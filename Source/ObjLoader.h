
//Author: Liuyi

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::getline;
using std::stringstream;
using std::cin;


#define TOKEN_POS "v"
#define TOKEN_NOR "vn"
#define TOKEN_VERTEX "vt"
#define TOKEN_FACE "f"

struct Vector2f
{
	float x,y;
};

struct Vector3f
{
	float x,y,z;
};

struct  ObjMeshVertex
{
	Vector3f pos;
	Vector2f texcoord;
	Vector3f normal;
};

/* This is a Quads, that we can render */
struct ObjMeshFace
{
	ObjMeshVertex vertices[4];
};

/* This contains a list of Quads */
struct ObjMesh
{
	vector<ObjMeshFace> faces;
};

/* Internal structure */

struct _ObjMeshFaceIndex{
    int pos_index[4];
    int tex_index[4];
    int nor_index[4];
};

ObjMesh LoadObjMesh(string filename);




