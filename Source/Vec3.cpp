#include "Vec3.h"

	Vec3::Vec3()
	{
		clear();
	}

	Vec3::Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	void Vec3::clear()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	void Vec3::setX(float x){X = x;}

	void Vec3::setY(float y){Y = y;}

	void Vec3::setZ(float z){Z = z;}

	float Vec3::getX(){return X;}

	float Vec3::getY(){return Y;}

	float Vec3::getZ(){return Z;}

	float Vec3::dotProd(Vec3 v)
	{
		return((this->getX()*v.getX()) + (this->getY()*v.getY()) + (this->getZ()*v.getZ()));
	}

	Vec3 Vec3::xProd(Vec3 v)
	{
		Vec3 cross;
		cross.setX( (this->getY()*v.getZ()) - (this->getZ()*v.getY()) );
		cross.setY( (this->getZ()*v.getX()) - (this->getX()*v.getZ()) );
		cross.setZ( (this->getX()*v.getY()) - (this->getY()*v.getX()) );

		return cross;
	}

	float Vec3::length()
	{
		return sqrt( (this->getX()*this->getX()) + (this->getY()*this->getY()) + (this->getZ()*this->getZ()) );
	}

	Vec3 Vec3::normalize()
	{
		float mag = length();
		Vec3 Normal;

		Normal.setX(this->getX()/mag);
		Normal.setY(this->getY()/mag);
		Normal.setZ(this->getZ()/mag);

		return Normal;
	}

	float Vec3::degreesToRadians(float deg)
	{
		const float pi = 3.14159f;
		return (deg / 180) * pi;
	}

	void Vec3::rotate(float angle)
	{
		this->setX(this->getX() * cos(angle) - this->getY() * sin(angle));
		this->setY(this->getX() * sin(angle) - this->getY() * cos(angle));
	}

	Vec3 Vec3::operator+ (Vec3 v)
	{
		Vec3 add((this->getX() + v.getX()),
				 (this->getY() + v.getY()),
				 (this->getZ() + v.getZ()));
		return add;
	 }

	Vec3 Vec3::operator- (Vec3 v)
	{
		Vec3 sub((this->getX() - v.getX()),
				 (this->getY() - v.getY()),
				 (this->getZ() - v.getZ()));
		return sub;
	 }

	Vec3 Vec3::operator* (float value)
	{
		Vec3 multi((this->getX() * value),
				   (this->getY() * value),
				   (this->getZ() * value));
		return multi;
	}

	void Vec3::operator= (Vec3 v)
	{
		this->setX(v.getX());
		this->setY(v.getY());
		this->setZ(v.getZ());
	 }

	Vec3 Vec3::operator+= (Vec3 v)
	{
		this->setX(this->getX() + v.getX());
		this->setY(this->getY() + v.getY());
		this->setZ(this->getZ() + v.getZ());
		return *this;
	}
	Vec3 Vec3::operator-= (Vec3 v)
	{
		this->setX(this->getX() - v.getX());
		this->setY(this->getY() - v.getY());
		this->setZ(this->getZ() - v.getZ());
		return *this;
	}

	bool Vec3::operator== (Vec3 v)
	{
		if(this->getX() == v.getX())
		{
			if(this->getY() == v.getY())
			{
				if(this->getZ() == v.getZ())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	float Vec3::operator*(Vec3 v)
    {
        return (this->getX()*v.getX() + this->getY()*v.getY() + this->getZ()*v.getZ());
    }


	void Vec3::rotateByPoint(Vec3 Center, float angle)
	{
		
		float radius = degreesToRadians(angle);
		float x = Center.getX() +  (this->getX() - Center.getX()) * cos(radius) - (this->getZ() - Center.getZ()) * sin(radius);
		float z = Center.getZ() +  (this->getX() - Center.getX()) * sin(radius) + (this->getZ() - Center.getZ()) * cos(radius);
		this->setX(x);
		this->setZ(z);
	}