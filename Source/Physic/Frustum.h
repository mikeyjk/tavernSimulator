#pragma once

#include "Plane.h"
#include "Bbox.h"


//Plane Test;
//Test.SetNormalAndPoint(Vec3(-1,0,0), Vec3(0,0,0));
//float a = Test.distance(Vec3(5,0,0));


class Frustum
{

public:
	
	static Frustum* Instance();
	~Frustum(void);

	static enum {OUTSIDE, INTERSECT, INSIDE};

	Plane Planes[6];

	Vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
	float nearD, farD, ratio, angle,tang;
	float nw,nh,fw,fh;

	
	void setCamInternals(float angle, float ratio, float nearD, float farD);
	void setCamDef(Vec3 p, Vec3 l, Vec3 u);
	int  pointInFrustum(Vec3 p);
	int  sphereInFrustum(Vec3 p, float raio);
	int  boxInFrustum(Bbox b);

	void drawPoints();
	void drawLines();
	void drawPlanes();
	void drawNormals();



private:

	enum {
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};

	Frustum(void);
};

