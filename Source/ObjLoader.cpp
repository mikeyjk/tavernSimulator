#include "ObjLoader.h"


/*
  
   Load the information in .obj file into Structure
   
   precondition:  The file must be .obj format, and the file should be exported by 3D Max

   postcondition: All the informtion be loaded into ObjMesh structure

   postcondition: Return the ObjMesh

*/

ObjMesh LoadObjMesh(string filename)
{
	ObjMesh myMesh;
	vector<Vector3f> positions;
	vector<Vector2f> texcoords;
	vector<Vector3f> normals;
	vector<_ObjMeshFaceIndex> faces;

	/**
	*   Load file, parse it
	*   Lines beginning with:
	*   '#' are comments can be ignored
	*   'v' are vertices positions
	*   'vt' are vertices texcoords
	*   'vn' are vertices normals
	*   'f' are faces
	*/

	ifstream filestream;
	filestream.open(filename);

	string line_stream;
	while(getline(filestream, line_stream))
	{
		stringstream str_stream(line_stream);
		string type_str;
		str_stream >> type_str;
		
		if(type_str == TOKEN_POS)
		{
           Vector3f pos;
		   str_stream >> pos.x >> pos.y >> pos.z;
		   positions.push_back(pos);
		}
		else if(type_str == TOKEN_VERTEX)
		{
			Vector2f tex;
			str_stream >> tex.x  >> tex.y;
			texcoords.push_back(tex);
		}
		else if(type_str == TOKEN_NOR)
		{
			Vector3f nor;
			str_stream >> nor.x >> nor.y >> nor.z;
			normals.push_back(nor);
		}
		else if(type_str == TOKEN_FACE)
		{
			_ObjMeshFaceIndex face_index;
			char interupt;
			for(int i = 0; i < 4; i++)
			{
				str_stream >> face_index.pos_index[i] >> interupt
					       >> face_index.tex_index[i] >> interupt
						   >> face_index.nor_index[i];

			}

			faces.push_back(face_index);
		}
	}

	filestream.close();

	for(int i = 0; i < faces.size(); i++)
	{
		ObjMeshFace face;
		for(int j =0; j <4; j++)
		{
			face.vertices[j].pos = positions[faces[i].pos_index[j] -1 ];
			face.vertices[j].texcoord   = texcoords[faces[i].tex_index[j] -1 ];
            face.vertices[j].normal     = normals[faces[i].nor_index[j] - 1 ];

		

		}
		myMesh.faces.push_back(face);
	}



	return myMesh;
}
