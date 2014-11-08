#include "Frustum.h"
#include "GL\freeglut.h"
#define ANG2RAD 3.14159265358979323846/180.0

Frustum::Frustum(void)
{
}


Frustum::~Frustum(void)
{
}

Frustum* Frustum::Instance()
{
	static Frustum instance;
	return &instance;
}

void Frustum::setCamInternals(float angle, float ratio, float Near, float Far)
{
	this->ratio = ratio;
	this->angle = angle;
	//distance from the viewpoint to Planesane
	this->nearD = Near;
	this->farD  = Far;

	tang = (float)tan(angle *ANG2RAD * 0.5);
	//compute the width and height of the near and far Planesane
	nh = nearD * tang;
	nw = nh * ratio;

	fh = farD * tang;
	fw = fh * ratio;
}


void Frustum::setCamDef(Vec3 pos, Vec3 lookat, Vec3 up)
{
	Vec3 dir, nc, fc, X, Y, Z;
	Z = pos - lookat;
	Z = Z.normalize();
	X = up.xProd(Z);
	X = X.normalize();
	Y = Z.xProd(X);

	//distance to the center of the near Planesane
	nc = pos -  Z * nearD;
	//distance to the center of the far Planesane
	fc = pos -  Z * farD;

	//near top left
	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;

	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;


	Planes[TOP].set3Points(ntr,ntl,ftl);
	Planes[BOTTOM].set3Points(nbl,nbr,fbr);
	Planes[LEFT].set3Points(ntl,nbl,fbl);
	Planes[RIGHT].set3Points(nbr,ntr,fbr);
	Planes[NEARP].set3Points(ntl,ntr,nbr);
	Planes[FARP].set3Points(ftr,ftl,fbl);

}








void Frustum::drawLines() {

	glLineWidth(3);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINE_LOOP);
	//near Planesane
		glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(nbr.X,nbr.Y,nbr.Z);
		glVertex3f(nbl.X,nbl.Y,nbl.Z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//far Planesane
		glVertex3f(ftr.X,ftr.Y,ftr.Z);
		glVertex3f(ftl.X,ftl.Y,ftl.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//bottom Planesane
		glVertex3f(nbl.X,nbl.Y,nbl.Z);
		glVertex3f(nbr.X,nbr.Y,nbr.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//top Planesane
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(ftl.X,ftl.Y,ftl.Z);
		glVertex3f(ftr.X,ftr.Y,ftr.Z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//left Planesane
		glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(nbl.X,nbl.Y,nbl.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);
		glVertex3f(ftl.X,ftl.Y,ftl.Z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// right Planesane
		glVertex3f(nbr.X,nbr.Y,nbr.Z);
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(ftr.X,ftr.Y,ftr.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);

	glEnd();
}


void Frustum::drawPlanes() {

	glBegin(GL_QUADS);

	//near Planesane
		glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(nbr.X,nbr.Y,nbr.Z);
		glVertex3f(nbl.X,nbl.Y,nbl.Z);

	//far Planesane
		glVertex3f(ftr.X,ftr.Y,ftr.Z);
		glVertex3f(ftl.X,ftl.Y,ftl.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);

	//bottom Planesane
		glVertex3f(nbl.X,nbl.Y,nbl.Z);
		glVertex3f(nbr.X,nbr.Y,nbr.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);

	//top Planesane
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(ftl.X,ftl.Y,ftl.Z);
		glVertex3f(ftr.X,ftr.Y,ftr.Z);

	//left Planesane

		glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(nbl.X,nbl.Y,nbl.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);
		glVertex3f(ftl.X,ftl.Y,ftl.Z);

	// right Planesane
		glVertex3f(nbr.X,nbr.Y,nbr.Z);
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(ftr.X,ftr.Y,ftr.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);

	glEnd();

}

void Frustum::drawNormals() {

	Vec3 a,b;

	glBegin(GL_LINES);

		// near
		a = (ntr + ntl + nbr + nbl) * 0.25;
		b = a + Planes[NEARP].normal;
		glVertex3f(a.X,a.Y,a.Z);
		glVertex3f(b.X,b.Y,b.Z);

		// far
		a = (ftr + ftl + fbr + fbl) * 0.25;
		b = a + Planes[FARP].normal;
		glVertex3f(a.X,a.Y,a.Z);
		glVertex3f(b.X,b.Y,b.Z);

		// left
		a = (ftl + fbl + nbl + ntl) * 0.25;
		b = a + Planes[LEFT].normal;
		glVertex3f(a.X,a.Y,a.Z);
		glVertex3f(b.X,b.Y,b.Z);
		
		// right
		a = (ftr + nbr + fbr + ntr) * 0.25;
		b = a + Planes[RIGHT].normal;
		glVertex3f(a.X,a.Y,a.Z);
		glVertex3f(b.X,b.Y,b.Z);
		
		// top
		a = (ftr + ftl + ntr + ntl) * 0.25;
		b = a + Planes[TOP].normal;
		glVertex3f(a.X,a.Y,a.Z);
		glVertex3f(b.X,b.Y,b.Z);
		
		// bottom
		a = (fbr + fbl + nbr + nbl) * 0.25;
		b = a + Planes[BOTTOM].normal;
		glVertex3f(a.X,a.Y,a.Z);
		glVertex3f(b.X,b.Y,b.Z);

	glEnd();


}


void Frustum::drawPoints() 
{

	glBegin(GL_POINTS);
	    glPointSize(3);
		glColor3f(0.0,1.0,0.0);
	    glVertex3f(ntl.X,ntl.Y,ntl.Z);
		glVertex3f(ntr.X,ntr.Y,ntr.Z);
		glVertex3f(nbl.X,nbl.Y,nbl.Z);
		glVertex3f(nbr.X,nbr.Y,nbr.Z);

		glVertex3f(ftl.X,ftl.Y,ftl.Z);
		glVertex3f(ftr.X,ftr.Y,ftr.Z);
		glVertex3f(fbl.X,fbl.Y,fbl.Z);
		glVertex3f(fbr.X,fbr.Y,fbr.Z);

	glEnd();
}

int Frustum::boxInFrustum(Bbox box)
{
	int result = INSIDE;
	for(int i=0; i < 6; i++) 
	{
		if( (Planes[i].distance( Vec3(box.LDB.x,box.LDB.y,box.LDB.z) ) < 0) && (Planes[i].distance( Vec3(box.RTF.x,box.RTF.y,box.RTF.z)) < 0))
			return OUTSIDE;
	}
	return result;
}