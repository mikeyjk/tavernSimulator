//
//  TextureManager.cpp
//  TextureManager
//
//  Created by Liu Yi on 21/10/13.
//  Last Modified on 30/03/14.
//

#include "TextureManager.h"

TextureManager* TextureManager::Instance()
{
	static TextureManager Instance;
	return &Instance;
}

void TextureManager::addTexture(char * Path, string Name)
{
	map<string, GLuint>::iterator iterator;
	iterator = textures.find(Name);
    
	if(iterator == textures.end())
	{
		GLint temp;
		temp = loadPNG(Path);
		textures.insert(pair<string, GLuint>(Name, temp));
	}
}

void TextureManager::printTexs()
{
	for(auto& i : textures)
	{
		std::cout << "texname: " << i.first << std::endl;
		std::cout << "texid: " << i.second << std::endl;
	}
}

void TextureManager::addCreatedTexture(GLuint tex, string Name)
{
	map<string, GLuint>::iterator iterator;
	iterator = textures.find(Name);
	if(iterator == textures.end())
	{
		textures.insert(pair<string, GLuint>(Name, tex));
	}
}

GLuint TextureManager::loadPNG(char * name)
{
	GLuint textureId;
	textureId = SOIL_load_OGL_texture(name, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textureId);
	return textureId;
}

GLuint TextureManager::getTexture(string name)
{
	map<string, GLuint>::iterator iterator;
	iterator = textures.find(name);
    
	if(iterator != textures.end())
	{
		return(iterator->second);
	}
	else
	{
		return(-1);
		std::cout << "Texture error!" << std::endl;
		exit(-1);
	}
}

void TextureManager::addCubeTexture(char * front, char * back, char * top, char * bottom, char * left, char * right, string name)
{
	map<string, GLuint>::iterator iterator;
	iterator = textures.find(name);

	if(iterator == textures.end())
	{
		GLuint temp;
		temp = loadCube(front,back,top,bottom,left,right);
		textures.insert(pair<string,GLuint>(name,temp));
	}
}

GLuint TextureManager::loadCube(char * front, char * back, char * top, char * bottom, char * left, char * right)
{
	GLuint textureId;
	textureId = SOIL_load_OGL_cubemap(right, left, top, bottom, back, front, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);//SOIL_FLAG_MIPMAPS
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	return textureId;
}