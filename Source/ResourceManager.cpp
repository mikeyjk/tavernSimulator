//
//  ResourceManager.cpp
//  ResourceManager
//
//  Created by Robert Herne on 30/03/14.
//  Last Modified on 30/03/14.
//

#include "ResourceManager.h"

ResourceManager* ResourceManager::Instance()
{
	static ResourceManager Instance;
	return &Instance;
}

void ResourceManager::addTexture(char * Path, string Name)
{
	TextureManager::Instance()->addTexture(Path, Name);
}

void addCreatedTexture(GLuint tex, string Name)
{
	TextureManager::Instance()->addCreatedTexture(tex, Name);
}

GLuint ResourceManager::getTexture(string Name)
{
	return TextureManager::Instance()->getTexture(Name);
}

void ResourceManager::addModel(string Path, string Name, Vec3 *min, Vec3 *max)
{
	ModelManager::instance()->addModel(Path, Name, min, max);
}

void ResourceManager::drawModel(string Name, string TName, float transparency, Vec3 transition, Vec3 rotation)
{
	ModelManager::instance()->draw(Name, TName, transparency, transition, rotation);
}

void ResourceManager::drawModel(string Name, string TName, float transparency, Vec3 transition, Vec3 rotation, Vec3 scale)
{
	ModelManager::instance()->draw(Name, TName, transparency, transition, rotation, scale);
}

/**
void ResourceManager::playSound(const string& filePath)
{
	SoundManager::instance()->playSound(filePath);
}

void ResourceManager::playBackgroundSound(const string& filePath)
{
	SoundManager::instance()->playBackgroundSound(filePath);
}

void ResourceManager::stopBackgroundSound()
{
	SoundManager::instance()->stopBackgroundSound();
}*/

void ResourceManager::GenerateShader(char * VS, char * PS, string name)
{
	ShaderManager::Instance()->GenerateShader(VS,PS,name);
}

GLuint ResourceManager::GetShaderProram(string name)
{
	return ShaderManager::Instance()->GetShaderProram(name);
}

void ResourceManager::addCubeTexture(char * front, char * back, char * top, char * bottom, char * left, char * right, string name)
{
    TextureManager::Instance()->addCubeTexture(front, back, top, bottom, left, right, name);
}