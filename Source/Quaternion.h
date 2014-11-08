

#pragma once;

#include <math.h>
#include "Vec3.h"

class Quaternion {
  
public:
	// components of a quaternion

  // default constructor
    Quaternion() 
	{
      W = 1.0;
      X = 0.0;
      Y = 0.0;
      Z = 0.0;
    }

  // initialized constructor

  Quaternion(float w, float x, float y, float z) 
  {
      W = w;
      X = x;
      Y = y;
      Z = z;
  }



  Quaternion(Vec3 axis, float angle)
  {
	  float sinHalfAngle = (float)sin(degreesToRadians(angle/2));
	  float cosHalfAngle = (float)cos(degreesToRadians(angle/2));

	  X = axis.getX() * sinHalfAngle;
	  Y = axis.getY() * sinHalfAngle;
	  Z = axis.getZ() * sinHalfAngle;
	  W = cosHalfAngle;

  }

  float degreesToRadians(float deg)
  {
		const float pi = 3.14159f;
		return (deg / 180) * pi;
  }

  float length()
  {
	  return (float)sqrt(X * X + Y * Y + Z * Z + W * W);
  }


  // quaternion multiplication
  inline Quaternion mult (Quaternion q) 
  {
    float w = W * q.W - (X * q.X + Y * q.Y + Z * q.Z);

    float x = W * q.X + q.W * X + Y * q.Z - Z * q.Y;

    float y = W * q.Y + q.W * Y + Z * q.X - X * q.Z;

    float z = W * q.Z + q.W * Z + X * q.Y - Y * q.X;

    //W = w;
    //X = x;
    //Y = y;
    //Z = z;

	return Quaternion(w,x,y,z);
  }



  inline Quaternion mult(Vec3 r)
  {

	  float w = -X * r.getX() - Y * r.getY() - Z * r.getZ();
	  float x =  W * r.getX() + Y * r.getZ() - Z * r.getY();
	  float y =  W * r.getY() + Z * r.getX() - X * r.getZ();
	  float z =  W * r.getZ() + X * r.getY() - Y * r.getX();

	  //W = w_;
	  //X = x_;
	  //Y = y_;
	  //Z = z_;

	  return Quaternion(w,x,y,z);
  }

  // conjugates the quaternion
  inline Quaternion conjugate () 
  {
    // X = -X;
     //Y = -Y;
     //Z = -Z;

    return Quaternion(W,-X,-Y,-Z);
  }



  // inverts the quaternion
 inline Quaternion Inverted() 
 {
    float len = length();
    if (len == 0.0)
      len = 1.0;

    float recip = 1.0 / len;

    float w =  W * recip;
    float x = -X * recip;
    float y = -Y * recip;
    float z = -Z * recip;

    return Quaternion(w,x,y,z);
  }

  // sets to unit quaternion
  Quaternion normalize() 
  {
    float len= length();
    if (len == 0.0)
    {
      W = 1.0; 
      X = Y = Z = 0.0;
    }
    else
    {
       X /= len;
	   Y /= len;
	   Z /= len;
	   W /= len;
    }
    return * this;
  }

  float getX()
  {
	  return X;
  }

  float getY()
  {
	  return Y;
  }

  float getZ()
  {
	  return Z;
  }



  float W, X, Y, Z;      

};
  /*
  // Makes quaternion from axis
 Quaternion fromAxis(float Angle, float x, float y, float z) { 
    float omega, s, c;
    int i;

    s = sqrt(x*x + y*y + z*z);

    if (abs(s) > Float.MIN_VALUE)
    {
      c = 1.0/s;

      x *= c;
      y *= c;
      z *= c;

      omega = -0.5f * Angle;
      s = (float)sin(omega);

      X = s*x;
      Y = s*y;
      Z = s*z;
      W = (float)cos(omega);
    }
    else
    {
      X = Y = 0.0f;
      Z = 0.0f;
      W = 1.0f;
    }
    normalize();
    return *this;
  }

  Quaternion fromAxis(float Angle, PVector axis) 
  {
    return this.fromAxis(Angle, axis.x, axis.y, axis.z);
  }

  // Rotates towards other quaternion
  public void slerp(Quaternion a, Quaternion b, float t)
  {
    float omega, cosom, sinom, sclp, sclq;
    int i;


    cosom = a.X*b.X + a.Y*b.Y + a.Z*b.Z + a.W*b.W;


    if ((1.0f+cosom) > Float.MIN_VALUE)
    {
      if ((1.0f-cosom) > Float.MIN_VALUE)
      {
        omega = acos(cosom);
        sinom = sin(omega);
        sclp = sin((1.0f-t)*omega) / sinom;
        sclq = sin(t*omega) / sinom;
      }
      else
      {
        sclp = 1.0f - t;
        sclq = t;
      }

      X = sclp*a.X + sclq*b.X;
      Y = sclp*a.Y + sclq*b.Y;
      Z = sclp*a.Z + sclq*b.Z;
      W = sclp*a.W + sclq*b.W;
    }
    else
    {
      X =-a.Y;
      Y = a.X;
      Z =-a.W;
      W = a.Z;

      sclp = sin((1.0f-t) * PI * 0.5);
      sclq = sin(t * PI * 0.5);

      X = sclp*a.X + sclq*b.X;
      Y = sclp*a.Y + sclq*b.Y;
      Z = sclp*a.Z + sclq*b.Z;
    }
  }

  public Quaternion exp()
  {                               
    float Mul;
    float Length = sqrt(X*X + Y*Y + Z*Z);

    if (Length > 1.0e-4)
      Mul = sin(Length)/Length;
    else
      Mul = 1.0;

    W = cos(Length);

    X *= Mul;
    Y *= Mul;
    Z *= Mul; 

    return this;
  }

  public Quaternion log()
  {
    float Length;

    Length = sqrt(X*X + Y*Y + Z*Z);
    Length = atan(Length/W);

    W = 0.0;

    X *= Length;
    Y *= Length;
    Z *= Length;

    return this;
  }


  public boolean equals(Quaternion r)
	{
		return x == r.getX() && y == r.getY() && z == r.getZ() && w == r.getW();
	}

  */

/*

public class Quaternion
{
	private float x;
	private float y;
	private float z;
	private float w;

	public Quaternion(float x, float y, float z, float w)
	{
		this.x = x;
		this.y = y;
		this.z = z;
		this.w = w;
	}

	public Quaternion(Vector3f axis, float angle)
	{
		float sinHalfAngle = (float)Math.sin(angle / 2);
		float cosHalfAngle = (float)Math.cos(angle / 2);

		this.x = axis.getX() * sinHalfAngle;
		this.y = axis.getY() * sinHalfAngle;
		this.z = axis.getZ() * sinHalfAngle;
		this.w = cosHalfAngle;
	}

	public float length()
	{
		return (float)Math.sqrt(x * x + y * y + z * z + w * w);
	}

	public Quaternion normalized()
	{
		float length = length();

		return new Quaternion(x / length, y / length, z / length, w / length);
	}

	public Quaternion conjugate()
	{
		return new Quaternion(-x, -y, -z, w);
	}

	public Quaternion mul(float r)
	{
		return new Quaternion(x * r, y * r, z * r, w * r);
	}

	public Quaternion mul(Quaternion r)
	{
		float w_ = w * r.getW() - x * r.getX() - y * r.getY() - z * r.getZ();
		float x_ = x * r.getW() + w * r.getX() + y * r.getZ() - z * r.getY();
		float y_ = y * r.getW() + w * r.getY() + z * r.getX() - x * r.getZ();
		float z_ = z * r.getW() + w * r.getZ() + x * r.getY() - y * r.getX();

		return new Quaternion(x_, y_, z_, w_);
	}

	public Quaternion mul(Vector3f r)
	{
		float w_ = -x * r.getX() - y * r.getY() - z * r.getZ();
		float x_ =  w * r.getX() + y * r.getZ() - z * r.getY();
		float y_ =  w * r.getY() + z * r.getX() - x * r.getZ();
		float z_ =  w * r.getZ() + x * r.getY() - y * r.getX();

		return new Quaternion(x_, y_, z_, w_);
	}

	public Matrix4f toRotationMatrix()
	{
		Vector3f forward =  new Vector3f(2.0f * (x*z - w*y), 2.0f * (y*z + w*x), 1.0f - 2.0f * (x*x + y*y));
		Vector3f up = new Vector3f(2.0f * (x*y + w*z), 1.0f - 2.0f * (x*x + z*z), 2.0f * (y*z - w*x));
		Vector3f right = new Vector3f(1.0f - 2.0f * (y*y + z*z), 2.0f * (x*y - w*z), 2.0f * (x*z + w*y));

		return new Matrix4f().initRotation(forward, up, right);
	}

	public Vector3f getForward()
	{
		return new Vector3f(0,0,1).rotate(this);
	}

	public Vector3f getBack()
	{
		return new Vector3f(0,0,-1).rotate(this);
	}

	public Vector3f getUp()
	{
		return new Vector3f(0,1,0).rotate(this);
	}

	public Vector3f getDown()
	{
		return new Vector3f(0,-1,0).rotate(this);
	}

	public Vector3f getRight()
	{
		return new Vector3f(1,0,0).rotate(this);
	}

	public Vector3f getLeft()
	{
		return new Vector3f(-1,0,0).rotate(this);
	}

	public Quaternion set(float x, float y, float z, float w) { this.x = x; this.y = y; this.z = z; this.w = w; return this; }
	public Quaternion set(Quaternion r) { set(r.getX(), r.getY(), r.getZ(), r.getW()); return this; }

	public float getX()
	{
		return x;
	}

	public void setX(float x)
	{
		this.x = x;
	}

	public float getY()
	{
		return y;
	}

	public void setY(float y)
	{
		this.y = y;
	}

	public float getZ()
	{
		return z;
	}

	public void setZ(float z)
	{
		this.z = z;
	}

	public float getW()
	{
		return w;
	}

	public void setW(float w)
	{
		this.w = w;
	}

	public boolean equals(Quaternion r)
	{
		return x == r.getX() && y == r.getY() && z == r.getZ() && w == r.getW();
	}
}
Status API Training Shop Blog About © 2014 GitHub, Inc. Terms Privacy Security Contact 
*/