#ifndef TEXTURE_GENERATOR_H 
#define TEXTURE_GENERATOR_H 
#if _MSC_VER >= 1020 
#pragma once 

/**
	*@class TextureGenerator
	*@brief The Texture Generator class creates a procedural terran texture for the terrain created
	*@author:  Karl Tysoe, Liu Yi
	*@inherits:  nil
	*@date 01/04/2014
	*
*/

template <class T>
struct RGB
{
	T r;
	T g;
	T b;
	void set(RGB<T> rgb){r=rgb.r;g=rgb.g;b=rgb.b;}
    void reset(){r=0;g=0;b=0;}
};

struct texture{
	unsigned char* tex;

	unsigned int size;
	RGB<unsigned char> getColor(int x, int y)
	{
		RGB<unsigned char> col;
		int spot = (x + (y*size))*3;
		col.b = tex[spot];
		col.g = tex[spot + 1];
		col.r = tex[spot + 2];

		return col;
	}

	unsigned int getWidth(){return size;}
	unsigned int getHeight(){return size;}
};
 
class textureGenerator 
{ 
private: 

	texture texArr[4];
	 //image* tex[4]; //textures 0-3, 4 in total 
	 unsigned char* newTex; 
	 int newTexWidth; 
	 int newTexHeight; 
	 int newTexBPP; // bytes per pixel 
	 int numTextures; 
	 int rangeCount;

public: 
	 textureGenerator(); 
	 ~textureGenerator(); 

	 void setRangeCount(int r){rangeCount = r;}

	 void addTexture(char* filename, int size); 
	 int getRangeCount(); 
	 bool isLoaded(int index); 
	 RGB<unsigned char> getColor(int texNum,int x, int y); 
	 void setColor(int x, int y, RGB<unsigned char> color); 
	 unsigned char* getTex(){return newTex;} 
	 bool setupNewTexture(int width, int height); 
	 float getRange(); 
	 float getTextureMax(int texNum); 
	 unsigned int getTexWidth(int texNo); 
	 unsigned int getTexHeight(int texNo); 

	 unsigned int getNewTexWidth(){return newTexWidth;} 
	 unsigned int getNewTexHeight(){return newTexHeight;} 

	 unsigned char * loadBMP(char * filename);
}; 

#endif
#endif