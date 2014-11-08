#ifndef GLWINDOWPOS_H
#define GLWINDOWPOS_H

#include <GL/freeglut.h>

void glWindowPos2s(short  x,short  y);
void glWindowPos2i(int    x,int    y);
void glWindowPos2f(float  x,float  y);
void glWindowPos2d(double x,double y);
void glWindowPos3s(short  x,short  y,short  z);
void glWindowPos3i(int    x,int    y,int    z);
void glWindowPos3f(float  x,float  y,float  z);
void glWindowPos3d(double x,double y,double z);
void glWindowPos4s(short  x,short  y,short  z,short  w);
void glWindowPos4i(int    x,int    y,int    z,int    w);
void glWindowPos4f(float  x,float  y,float  z,float  w);
void glWindowPos4d(double x,double y,double z,double w);
void glWindowPos2sv(const short  v[2]);
void glWindowPos2iv(const int    v[2]);
void glWindowPos2fv(const float  v[2]);
void glWindowPos2dv(const double v[2]);
void glWindowPos3sv(const short  v[3]);
void glWindowPos3iv(const int    v[3]);
void glWindowPos3fv(const float  v[3]);
void glWindowPos3dv(const double v[3]);
void glWindowPos4sv(const short  v[4]);
void glWindowPos4iv(const int    v[4]);
void glWindowPos4fv(const float  v[4]);
void glWindowPos4dv(const double v[4]);


void glWindowPos4f(float x,float y,float z,float w)
{
   //  Integer versions of x and y
   int ix = (int)x;
   int iy = (int)y;
   //  Save transform attributes (Matrix Mode and Viewport)
   glPushAttrib(GL_TRANSFORM_BIT|GL_VIEWPORT_BIT);
   //  Save projection matrix and set identity
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   //  Save model view matrix and set to indentity
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   //  Set viewport to 2x2 pixels around (x,y)
   glViewport(ix-1,iy-1,2,2);
   //  Finally set the raster position
   glRasterPos4f(x-ix,y-iy,z,w);
   //  Reset model view matrix
   glPopMatrix();
   //  Reset projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   //  Pop transform attributes (Matrix Mode and Viewport)
   glPopAttrib();
}

/*
 *  glWindowPos wrappers
 */
void glWindowPos2s(short  x,short  y)                   {glWindowPos4f(x,y,0,1);}
void glWindowPos2i(int    x,int    y)                   {glWindowPos4f(x,y,0,1);}
void glWindowPos2f(float  x,float  y)                   {glWindowPos4f(x,y,0,1);}
void glWindowPos2d(double x,double y)                   {glWindowPos4f(x,y,0,1);}
void glWindowPos3s(short  x,short  y,short  z)          {glWindowPos4f(x,y,z,1);}
void glWindowPos3i(int    x,int    y,int    z)          {glWindowPos4f(x,y,z,1);}
void glWindowPos3f(float  x,float  y,float  z)          {glWindowPos4f(x,y,z,1);}
void glWindowPos3d(double x,double y,double z)          {glWindowPos4f(x,y,z,1);}
void glWindowPos4s(short  x,short  y,short  z,short  w) {glWindowPos4f(x,y,z,w);}
void glWindowPos4i(int    x,int    y,int    z,int    w) {glWindowPos4f(x,y,z,w);}
void glWindowPos4d(double x,double y,double z,double w) {glWindowPos4f(x,y,z,w);}
void glWindowPos2sv(const short  v[2])                  {glWindowPos4f(v[0],v[1],  0 ,  1 );}
void glWindowPos2iv(const int    v[2])                  {glWindowPos4f(v[0],v[1],  0 ,  1 );}
void glWindowPos2fv(const float  v[2])                  {glWindowPos4f(v[0],v[1],  0 ,  1 );}
void glWindowPos2dv(const double v[2])                  {glWindowPos4f(v[0],v[1],  0 ,  1 );}
void glWindowPos3sv(const short  v[3])                  {glWindowPos4f(v[0],v[1],v[2],  1 );}
void glWindowPos3iv(const int    v[3])                  {glWindowPos4f(v[0],v[1],v[2],  1 );}
void glWindowPos3fv(const float  v[3])                  {glWindowPos4f(v[0],v[1],v[2],  1 );}
void glWindowPos3dv(const double v[3])                  {glWindowPos4f(v[0],v[1],v[2],  1 );}
void glWindowPos4sv(const short  v[4])                  {glWindowPos4f(v[0],v[1],v[2],v[3]);}
void glWindowPos4iv(const int    v[4])                  {glWindowPos4f(v[0],v[1],v[2],v[3]);}
void glWindowPos4fv(const float  v[4])                  {glWindowPos4f(v[0],v[1],v[2],v[3]);}
void glWindowPos4dv(const double v[4])                  {glWindowPos4f(v[0],v[1],v[2],v[3]);}


#endif
