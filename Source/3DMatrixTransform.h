//Author: Liuyi

#pragma once

#include "Vec3.h"
#include <math.h>


/*
    This class for basical  Matrix Transformation

	Precondition: Load Identity Matrix first, and then Create Transformation Matrix
	
	Postcondition: Pass the Vector which you want to Translate in by reference.

	Postcondition: Finish Translate
*/
class C3DMatrix
{
private:

	struct Matrix
	{
		double _11, _12, _13, _14;
		double _21, _22, _23, _24;
		double _31, _32, _33, _34;
		double _41, _42, _43, _44;

		Matrix()
		{
			_11 = 0.0;  _12 = 0.0; _13 = 0.0; _14 = 0.0;
			_21 = 0.0;  _22 = 0.0; _23 = 0.0; _24 = 0.0;
			_31 = 0.0;  _32 = 0.0; _33 = 0.0; _34 = 0.0;
			_41 = 0.0;  _42 = 0.0; _43 = 0.0; _44 = 0.0;
		}

	};

	Matrix m_Matrix;

	inline void MatrixMultiply(Matrix & mIn);

public:

	C3DMatrix()
	{
		CreateIdentity();
	}

	//create an identity matrix
	inline void CreateIdentity();

	 //create a transformation matrix
	inline void CreateTranslateMatrix(double x, double y, double z);

	  //create a scale matrix
	inline void CreateScaleMatrix(double xScale, double yScale, double zScale);

	//Create a rotation matrix
	inline void CreateRotateMatByX(double randians);
	inline void CreateRotateMatByY(double randians);
	inline void CreateRotateMatByZ(double randians);

	//applys a transformation matrix to a Vector
	inline void TransformVector3D(Vec3 &Vec);

	inline float degreesToRadians(float deg);
	

	//accessor to the Matrix elements
	void _11(double val) {m_Matrix._11 = val;}
	void _12(double val) {m_Matrix._12 = val;}
	void _13(double val){m_Matrix._13 = val;}
	void _14(double val){m_Matrix._14 = val;}

	void _21(double val){m_Matrix._21 = val;}
	void _22(double val){m_Matrix._22 = val;}
	void _23(double val){m_Matrix._23 = val;}
	void _24(double val){m_Matrix._24 = val;}

	void _31(double val){m_Matrix._31 = val;}
	void _32(double val){m_Matrix._32 = val;}
	void _33(double val){m_Matrix._33 = val;}
	void _34(double val){m_Matrix._34 = val;}


	void _41(double val){m_Matrix._41 = val;}
	void _42(double val){m_Matrix._42 = val;}
	void _43(double val){m_Matrix._43 = val;}
	void _44(double val){m_Matrix._44 = val;}
};


//multiply two matrices together
inline void C3DMatrix::MatrixMultiply(Matrix &mIn)
{
	C3DMatrix::Matrix mat_temp;


  //firstrow
  mat_temp._11 = (m_Matrix._11*mIn._11) + (m_Matrix._12*mIn._21) + (m_Matrix._13*mIn._31) + (m_Matrix._14*mIn._41);
  mat_temp._12 = (m_Matrix._11*mIn._12) + (m_Matrix._12*mIn._22) + (m_Matrix._13*mIn._32) + (m_Matrix._14*mIn._42);
  mat_temp._13 = (m_Matrix._11*mIn._13) + (m_Matrix._12*mIn._23) + (m_Matrix._13*mIn._33) + (m_Matrix._14*mIn._43);
  mat_temp._14 = (m_Matrix._11*mIn._14) + (m_Matrix._12*mIn._24) + (m_Matrix._13*mIn._34) + (m_Matrix._14*mIn._44);

  //second
  mat_temp._21 = (m_Matrix._21*mIn._11) + (m_Matrix._22*mIn._21) + (m_Matrix._23*mIn._31) + (m_Matrix._24*mIn._41);
  mat_temp._22 = (m_Matrix._21*mIn._12) + (m_Matrix._22*mIn._22) + (m_Matrix._23*mIn._32) + (m_Matrix._24*mIn._42);
  mat_temp._23 = (m_Matrix._21*mIn._13) + (m_Matrix._22*mIn._23) + (m_Matrix._23*mIn._33) + (m_Matrix._24*mIn._43);
  mat_temp._24 = (m_Matrix._21*mIn._14) + (m_Matrix._22*mIn._24) + (m_Matrix._23*mIn._34) + (m_Matrix._24*mIn._44);

  //third
  mat_temp._31 = (m_Matrix._31*mIn._11) + (m_Matrix._32*mIn._21) + (m_Matrix._33*mIn._31) + (m_Matrix._34*mIn._41);
  mat_temp._32 = (m_Matrix._31*mIn._12) + (m_Matrix._32*mIn._22) + (m_Matrix._33*mIn._32) + (m_Matrix._34*mIn._42);
  mat_temp._33 = (m_Matrix._31*mIn._13) + (m_Matrix._32*mIn._23) + (m_Matrix._33*mIn._33) + (m_Matrix._34*mIn._43);
  mat_temp._34 = (m_Matrix._31*mIn._14) + (m_Matrix._32*mIn._24) + (m_Matrix._33*mIn._34) + (m_Matrix._34*mIn._44);

  //forth
  mat_temp._41 = (m_Matrix._41*mIn._11) + (m_Matrix._42*mIn._21) + (m_Matrix._43*mIn._31) + (m_Matrix._44*mIn._41);
  mat_temp._42 = (m_Matrix._41*mIn._12) + (m_Matrix._42*mIn._22) + (m_Matrix._43*mIn._32) + (m_Matrix._44*mIn._42);
  mat_temp._43 = (m_Matrix._41*mIn._13) + (m_Matrix._42*mIn._23) + (m_Matrix._43*mIn._33) + (m_Matrix._44*mIn._43);
  mat_temp._44 = (m_Matrix._41*mIn._14) + (m_Matrix._42*mIn._24) + (m_Matrix._43*mIn._34) + (m_Matrix._44*mIn._44);

  m_Matrix = mat_temp;

}


//create an identity matrix
inline void C3DMatrix::CreateIdentity()
{
	m_Matrix._11 = 1;  m_Matrix._12 = 0;  m_Matrix._13 = 0;  m_Matrix._14 = 0;
	m_Matrix._21 = 0;  m_Matrix._22 = 1;  m_Matrix._23 = 0;  m_Matrix._24 = 0;
	m_Matrix._31 = 0;  m_Matrix._32 = 0;  m_Matrix._33 = 1;  m_Matrix._34 = 0;
	m_Matrix._41 = 0;  m_Matrix._42 = 0;  m_Matrix._43 = 0;  m_Matrix._44 = 1;

}



//create a transformation matrix
inline void C3DMatrix::CreateTranslateMatrix(double x, double y, double z)
{
	 C3DMatrix::Matrix mat;

	 mat._11 = 1; mat._12  = 0 ; mat._13 = 0 ; mat._14 = x;
	 mat._21 = 0; mat._22  = 1 ; mat._23 = 0 ; mat._24 = y;
	 mat._31 = 0; mat._32  = 0 ; mat._33 = 1 ; mat._34 = z;
	 mat._41 = 0; mat._42  = 0 ; mat._43 = 0 ; mat._44 = 1;
	 
	 MatrixMultiply(mat);
}

//create a scale matrix
inline void C3DMatrix::CreateScaleMatrix(double xScale, double yScale, double zScale)
{

	 C3DMatrix::Matrix mat;
	 mat._11 = xScale ; mat._12  = 0      ; mat._13 = 0      ; mat._14 = 0;
	 mat._21 = 0      ; mat._22  = yScale ; mat._23 = 0      ; mat._24 = 0;
	 mat._31 = 0      ; mat._32  = 0      ; mat._33 = zScale ; mat._34 = 0;
	 mat._41 = 0      ; mat._42  = 0      ; mat._43 = 0      ; mat._44 = 1;
	 MatrixMultiply(mat);
}


inline void C3DMatrix::CreateRotateMatByX(double deg)
{
	C3DMatrix::Matrix mat;
	double Sin = sin(degreesToRadians(deg));
	double Cos = cos(degreesToRadians(deg));

	
	 mat._11 = 1; mat._12  = 0 ;   mat._13 = 0 ;    mat._14 = 0;
	 mat._21 = 0; mat._22  = Cos ; mat._23 = -Sin ; mat._24 = 0;
	 mat._31 = 0; mat._32  = Sin ; mat._33 = Cos ;  mat._34 = 0;
	 mat._41 = 0; mat._42  = 0 ;   mat._43 = 0 ;    mat._44 = 1;


	MatrixMultiply(mat);
}



inline void C3DMatrix::CreateRotateMatByY(double deg)
{
	C3DMatrix::Matrix mat;
	double Sin = sin(degreesToRadians(deg));
	double Cos = cos(degreesToRadians(deg));
	
	 mat._11 = Cos; mat._12  =  0;   mat._13 = Sin;     mat._14 = 0;
	 mat._21 = 0;   mat._22  =  1;   mat._23 = 0;       mat._24 = 0;
	 mat._31 = -Sin;mat._32  =  0;   mat._33 = Cos;     mat._34 = 0;
	 mat._41 = 0   ;mat._42  =  0;   mat._43 = 0;       mat._44 = 1;

	MatrixMultiply(mat);
}

inline void C3DMatrix::CreateRotateMatByZ(double deg)
{
	C3DMatrix::Matrix mat;
	double Sin = sin(degreesToRadians(deg));
	double Cos = cos(degreesToRadians(deg));
	
	 mat._11 = Cos; mat._12  =  -Sin;   mat._13 = 0;     mat._14 = 0;
	 mat._21 = Sin; mat._22  =  Cos;    mat._23 = 0;     mat._24 = 0;
	 mat._31 = 0 ;  mat._32  =  0;      mat._33 = 1;     mat._34 = 0;
	 mat._41 = 0   ;mat._42  =  0;      mat._43 = 0;     mat._44 = 1;

	MatrixMultiply(mat);
}

//Apply transformation to a Vector
inline void C3DMatrix::TransformVector3D(Vec3 &Vec)
{
	double tempX = (m_Matrix._11 * Vec.getX() ) + (m_Matrix._12 * Vec.getY()) + (m_Matrix._13 * Vec.getZ()) + (m_Matrix._14 * 0);
	double tempY = (m_Matrix._21 * Vec.getX() ) + (m_Matrix._22 * Vec.getY()) + (m_Matrix._23 * Vec.getZ()) + (m_Matrix._24 * 0);
	double tempZ = (m_Matrix._31 * Vec.getX() ) + (m_Matrix._32 * Vec.getY()) + (m_Matrix._33 * Vec.getZ()) + (m_Matrix._34 * 0);

	
	Vec.setX(tempX);
	Vec.setY(tempY);
	Vec.setZ(tempZ);
}

inline float C3DMatrix::degreesToRadians(float deg)
{
	const float pi = 3.14159f;
	return (deg / 180) * pi;	
}