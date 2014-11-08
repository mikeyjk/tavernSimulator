//
//  ModelManager.cpp
//  ModelManager
//
//  Created by Liu Yi on 28/10/13.
//  Last Modified on 30/03/14.
//

#include "ModelManager.h"
#include "GL\glext.h"


ModelManager* ModelManager::instance()
{
	static ModelManager Instance;
	return &Instance;
}

void ModelManager::addModel(string Path, string name, Vec3 *min, Vec3 *max)
{
	map<string, ObjMesh>::iterator iterator;
	iterator = models.find(name);
	if(iterator == models.end())
	{
		ObjMesh tempObj;
		tempObj = LoadObjMesh(Path);
		models.insert(pair<string, ObjMesh>(name,tempObj));

		std::vector<float> ALL;
		std::vector<float> ALLT;
		std::vector<float> ALLN;
		for(int i = 0; i < tempObj.faces.size(); i++)
		{
			ObjMeshFace& current_face = tempObj.faces[i];
			for(int j = 0; j < 4; j++)
			{
		
				if(j != 3)
				{
					ObjMeshVertex& vertex = current_face.vertices[j];
					//Find min and max of X
					ALL.push_back(vertex.pos.x);
					if(vertex.pos.x < min->getX())
						min->setX(vertex.pos.x);
					if(vertex.pos.x > max->getX())
						max->setX(vertex.pos.x);
					
					//Find min and max of Y
					ALL.push_back(vertex.pos.y);
					if(vertex.pos.y < min->getY())
						min->setY(vertex.pos.y);
					if(vertex.pos.y > max->getY())
						max->setY(vertex.pos.y);

					//Find min and max of Z
					ALL.push_back(vertex.pos.z);
					if(vertex.pos.z < min->getZ())
						min->setZ(vertex.pos.z);
					if(vertex.pos.z > max->getZ())
						max->setZ(vertex.pos.z);

					ALLT.push_back(vertex.texcoord.x);
					ALLT.push_back(vertex.texcoord.y);
					ALLN.push_back(vertex.normal.x);
					ALLN.push_back(vertex.normal.y);
					ALLN.push_back(vertex.normal.z);
				}
				else
				{
					ObjMeshVertex& vertex = current_face.vertices[j-3];
					
					//Find min and max of X
					ALL.push_back(vertex.pos.x);
					if(vertex.pos.x < min->getX())
						min->setX(vertex.pos.x);
					if(vertex.pos.x > max->getX())
						max->setX(vertex.pos.x);
					
					//Find min and max of Y
					ALL.push_back(vertex.pos.y);
					if(vertex.pos.y < min->getY())
						min->setY(vertex.pos.y);
					if(vertex.pos.y > max->getY())
						max->setY(vertex.pos.y);

					//Find min and max of Z
					ALL.push_back(vertex.pos.z);
					if(vertex.pos.z < min->getZ())
						min->setZ(vertex.pos.z);
					if(vertex.pos.z > max->getZ())
						max->setZ(vertex.pos.z);

					ALLT.push_back(vertex.texcoord.x);
					ALLT.push_back(vertex.texcoord.y);
					ALLN.push_back(vertex.normal.x);
					ALLN.push_back(vertex.normal.y);
					ALLN.push_back(vertex.normal.z);

					vertex = current_face.vertices[j-1];
					ALL.push_back(vertex.pos.x);
					ALL.push_back(vertex.pos.y);
					ALL.push_back(vertex.pos.z);
					ALLT.push_back(vertex.texcoord.x);
					ALLT.push_back(vertex.texcoord.y);
					ALLN.push_back(vertex.normal.x);
					ALLN.push_back(vertex.normal.y);
					ALLN.push_back(vertex.normal.z);
					
					vertex = current_face.vertices[j];
					ALL.push_back(vertex.pos.x);
					ALL.push_back(vertex.pos.y);
					ALL.push_back(vertex.pos.z);
					ALLT.push_back(vertex.texcoord.x);
					ALLT.push_back(vertex.texcoord.y);
					ALLN.push_back(vertex.normal.x);
					ALLN.push_back(vertex.normal.y);
					ALLN.push_back(vertex.normal.z);
				}
			}

		}

		GLuint elementbuffer;
		GLuint textureCoor;
		GLuint Texnormal;
		
		float * model = new float[ALL.size()];
		for(int i = 0; i < ALL.size(); i++)
		{
			model[i] = ALL[i];
		}

		float * texture = new float[ALLT.size()];
		for(int i = 0; i < ALLT.size(); i++)
		{
			texture[i] = ALLT[i];
		}

		float * normal = new float[ALLN.size()];
		for(int i = 0; i < ALLN.size(); i++)
		{
			normal[i] = ALLN[i];
		}

		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ARRAY_BUFFER, ALL.size() * sizeof(float), model, GL_STATIC_DRAW);
	
		glGenBuffers(1, &textureCoor);
		glBindBuffer(GL_ARRAY_BUFFER, textureCoor);
		glBufferData(GL_ARRAY_BUFFER, ALLT.size() * sizeof(float), texture, GL_STATIC_DRAW);

		glGenBuffers(1, &Texnormal);
		glBindBuffer(GL_ARRAY_BUFFER, Texnormal);
		glBufferData(GL_ARRAY_BUFFER, ALLN.size() * sizeof(float), normal, GL_STATIC_DRAW);

		modelvertex.insert(pair<string, GLuint>(name,elementbuffer));
		modeltexture.insert(pair<string, GLuint>(name,textureCoor));
		modelNormal.insert(pair<string, GLuint>(name,Texnormal));
		NumberOfVertex.insert(pair<string,int>(name,ALL.size()));

		delete[] model;
		delete[] texture;
		delete[] normal;

		MinMax temp;
		temp.min.X = min->X;
		temp.min.Y = min->Y;
		temp.min.Z = min->Z;

		temp.max.X = max->X;
		temp.max.Y = max->Y;
		temp.max.Z = max->Z;

		modelMinMax.insert(pair<string,MinMax>(name, temp));
	}
	else
	{
		map<string, MinMax>::iterator iterator;
		iterator = modelMinMax.find(name);
		if(iterator != modelMinMax.end())
		{
			min->X = iterator->second.min.X;
			min->Y = iterator->second.min.Y;
			min->Z = iterator->second.min.Z;

			max->X = iterator->second.max.X;
			max->Y = iterator->second.max.Y;
			max->Z = iterator->second.max.Z;
		}
	}
}

GLuint ModelManager::getModelVertex(string name)
{
	map<string, GLuint>::iterator iterator;
	iterator = modelvertex.find(name);
	if(iterator != modelvertex.end())
	{
		return (iterator->second);
	}

	cout << "The 3D model " << name << " does not exist in the Manager" << endl;
	return -1;
}

GLuint ModelManager::getTexture(string name)
{
	map<string, GLuint>::iterator iterator;
	iterator = modeltexture.find(name);
    
	if(iterator != modeltexture.end())
	{
		return (iterator->second);
	}

	return -1;
}

GLuint ModelManager::getNormal(string name)
{
	map<string, GLuint>::iterator iterator;
	iterator = modelNormal.find(name);
    
	if(iterator != modelNormal.end())
	{
		return (iterator->second);
	}

	return -1;
}

int ModelManager::getNumberOfVertices(string name)
{
	map<string, int>::iterator iterator;
	iterator = NumberOfVertex.find(name);
    
	if(iterator != NumberOfVertex.end())
	{
		return (iterator->second);
	}

	return -1;
}

void ModelManager::draw(string mName,string tName, float transparency , Vec3 transition, Vec3 rotation)
{
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, transparency);
	
	glRotatef(rotation.getX(), 1,0,0);
	glRotatef(rotation.getY(), 0,1,0);
	glRotatef(rotation.getZ(), 0,0,1);
	glTranslatef(transition.getX(), transition.getY(), transition.getZ());
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.1);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, getTexture(mName));
	glTexCoordPointer(2,GL_FLOAT,0,0);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureManager::Instance()->getTexture(tName));

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, getNormal(mName));
	glNormalPointer(GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER, getModelVertex(mName));
	glVertexPointer(3, GL_FLOAT, 0, 0); //0 is mean offset
	
	glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices(mName)); //0 start p

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	//glDisable(GL_BLEND);

	//glDisable(GL_ALPHA_TEST);
	 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glPopMatrix();
}

void ModelManager::draw(string mName, string tName, float transparency, Vec3 transition, Vec3 rotation, Vec3 scale)
{
	glPushMatrix();
	glColor4f(1.0,1.0,1.0,transparency);
	//glRotatef(rotation.getX() * (180/boost::math::constants::pi<long double>()), 1,0,0);
	//glRotatef(rotation.getY() * (180/boost::math::constants::pi<long double>()), 0,1,0);
	//glRotatef(rotation.getZ() * (180/boost::math::constants::pi<long double>()), 0,0,1);
	glScalef(scale.getX(), scale.getY(), scale.getZ());
	
	
	glRotatef(rotation.getX(), 1,0,0);
	glRotatef(rotation.getY(), 0,1,0);
	glRotatef(rotation.getZ(), 0,0,1);
	glTranslatef(transition.getX(), transition.getY(), transition.getZ());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, getTexture(mName));
	glTexCoordPointer(2,GL_FLOAT,0,0);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureManager::Instance()->getTexture(tName));

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, getNormal(mName));
	glNormalPointer(GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER, getModelVertex(mName));
	glVertexPointer(3, GL_FLOAT, 0, 0); //0 is mean offset
	
	glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices(mName)); //0 start p

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

  	glDisable(GL_BLEND);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glPopMatrix();
}