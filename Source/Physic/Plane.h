#pragma once

#include "../Vec3.h"

class Plane
{
public:
	Plane(void){}
	~Plane(void){}

	Vec3 normal;
	Vec3 point;
	float d;

	Plane( Vec3 p1,  Vec3 p2,  Vec3 p3);

	void set3Points( Vec3 p1,  Vec3 p2,  Vec3 p3);

	void SetNormalAndPoint(Vec3 normal, Vec3 point);

	void SetCoefficient(float a, float b, float c, float d);

	float distance(Vec3 p);

};

