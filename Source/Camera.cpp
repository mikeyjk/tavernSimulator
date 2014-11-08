#include "Camera.h"
#include "3DMatrixTransform.h"
#include "Quaternion.h"
#include <iostream>
#include <math.h>
#include "World.h"

Camera * Camera::Instance()
{
	static Camera Instance;
	return &Instance;
}



Camera::Camera(void)
{
	Position =  Vec3(0,0,-5);
	Up = Vec3(0.0,1.0,0.0);
	Target = Vec3(0.0,0.0,0.0);
	Speed = 6;

	Direction = (Target - Position).normalize();
	X_degree_difference = 0;
	Y_degree_difference = 0;
}


Camera::~Camera(void)
{
}


Vec3 Camera::GetPosition()
{
	return Position;
}
Vec3 Camera::GetUp()
{
	return Up;
}
Vec3 Camera::GetDirection()
{
	return Direction;
}

Vec3 Camera::GetSide()
{
	return (Up.xProd(GetDirection())).normalize();
}

Vec3 Camera::GetTarget()
{
	return Target;
}



void Camera::SetPosition(Vec3 v)
{
	Position = v;
}

void Camera::SetUp(Vec3 v)
{
	Up = v;
}

void Camera::SetTarget(Vec3 v)
{
	Target = v;
}


float Camera::GetSpeed()
{
	return Speed;
}


void Camera::SetSpeed(float num)
{
	Speed = num;
}

void Camera::SetDirection(Vec3 v)
{
	Direction = v;
}

void Camera::UpdateRotation()
{
	const float PI = 3.14159265;
   
	
	Vec3 tempZ  = Vec3(Direction.getX(), 0 , Direction.getZ()).normalize();
	Vec3 valueZ = tempZ.xProd(Vec3(0.0, 0.0, 1.0));
		 

	Vec3 tempY  = Vec3(0,  Direction.getY(), 1.0).normalize();
	Vec3 valueY = tempY.xProd(Vec3(0.0,0.0,1.0));

	if(valueZ.getY() >= 0)
	{
		X_degree_difference = acos(tempZ.dotProd(Vec3(0.0, 0.0, 1.0))) * 180.0/PI;
	}
	else if(valueZ.getY() < 0)
	{
		X_degree_difference = 360.0 - acos(tempZ.dotProd(Vec3(0.0, 0.0, 1.0))) * 180.0/PI;
	}
	
    //std::cout << " valueY.getX " <<   valueY.getX() << std::endl;
	if(valueY.getX() >= 0)
	{
       Y_degree_difference = acos(tempY.dotProd(Vec3(0.0,0.0,1.0))) * 180.0/PI;
	   //std::cout << " difference " <<   Y_degree_difference << std::endl;
	}
	else if(valueY.getX() < 0)
	{
	   Y_degree_difference = 360.0 - acos(tempY.dotProd(Vec3(0.0, 0.0, 1.0))) * 180.0/PI;
	   //std::cout << " difference " <<   Y_degree_difference << std::endl;
	}
	

}

void Camera::RotateYaw(float num)
{
	Quaternion rotation(Up, num/30);
	Quaternion Conjugate = rotation.conjugate();
	Quaternion result =  (rotation.mult(Direction)).mult(Conjugate);

	SetDirection(Vec3(result.getX(), result.getY(), result.getZ()));
	UpdateRotation();

}

void Camera::RotatePitch(float num)
{
	Quaternion rotation(GetSide(), num/30);
	Quaternion Conjugate = rotation.conjugate();
	Quaternion result =  (rotation.mult(Direction)).mult(Conjugate);
	Quaternion result_2 = (rotation.mult(Up)).mult(Conjugate);

	SetDirection(Vec3(result.getX(), result.getY(), result.getZ()));
	UpdateRotation();
}

void Camera::RotatePitch3rd(float num)
{
	
	Quaternion rotation(GetSide(), num/30);
	Quaternion Conjugate = rotation.conjugate();
	Quaternion result =  (rotation.mult(Direction)).mult(Conjugate);
	Quaternion result_2 = (rotation.mult(Up)).mult(Conjugate);


	SetDirection(Vec3(result.getX(), result.getY(), result.getZ()));
	UpdateRotation();
	
}

void Camera::RotateYaw3rd(float num)
{


	Vec3 tempCenter(World::Instance()->GetMainCharacter()->getPos().getX(),
		            World::Instance()->GetMainCharacter()->getPos().getY(),
					World::Instance()->GetMainCharacter()->getPos().getZ());

	Vec3 tempCamer(Position.getX(),
		           Position.getY(),
				   Position.getZ());

	tempCamer.rotateByPoint(tempCenter, -num/30);
	SetPosition(tempCamer);


	static float Rotation = 0;
	Rotation += num/30;

	if(Rotation < 0)
	{
		Rotation += 360;
	}
	else if(Rotation > 360)
	{
		Rotation -= 360; 
	}

	//just for rotate the Character
	World::Instance()->GetMainCharacter()->setRotation(0,Rotation, 0);
	
	Quaternion rotation(Up, num/30);
	Quaternion Conjugate = rotation.conjugate();
	Quaternion result =  (rotation.mult(Direction)).mult(Conjugate);
	SetDirection(Vec3(result.getX(), result.getY(), result.getZ()));

	UpdateRotation();
}



float Camera::GetRotateX()
{
	return X_degree_difference;
}

float Camera::GetRotateY()
{
	return Y_degree_difference;
}