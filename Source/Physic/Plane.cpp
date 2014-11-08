#include "Plane.h"


Plane::Plane( Vec3 p1,  Vec3 p2,  Vec3 p3)
{

}

void Plane::set3Points( Vec3 p1,  Vec3 p2,  Vec3 p3)
{
	Vec3 temp1, temp2;
	temp1 = p1 - p2;
	temp2 = p3 - p2;
	this->normal = temp2.xProd(temp1);
	this->normal.normalize();
	this->point = p2;
	this->d = (normal.dotProd(point));
}


void Plane::SetNormalAndPoint(Vec3 normal, Vec3 Point)
{
	this->normal = normal;
	this->normal.normalize();
	this->d = (normal.dotProd(point));
}


void Plane::SetCoefficient(float a, float b, float c, float d)
{
	this->normal.setX(a);
	this->normal.setY(b);
	this->normal.setZ(c);
	float length = normal.length();
	this->normal.normalize();
	this->d = d;
}


float Plane::distance(Vec3 p)
{
	return (normal.dotProd(p) - d);
}