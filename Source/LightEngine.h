#ifndef LIGHT_ENGINE_H
#define LIGHT_ENGINE_H

/**
	*@class LightEngine
	*@brief This Class is a very basic encapsulation of openGLs lighting
	*		Enables the user to specify up to 8 lights(openGLs restriction)
	*		Lightdata is stored in an array of LightParam objects
	*@author:  Karl Tysoe
	*@inherits:  null
	*@todo separate initialising of lights out of constructor
	*		Create a function for the light effects
	*@date 26/08/2014
	*
*/

#include "GL\freeglut.h"
#include "Vec3.h"

/**
		*@brief stuct lightParams
		*
		* this holds all of the values to create a light
		* specular, ambient, diffuse are arrays that hold the colour values
		* active is used if you want to toggle light on or off
		* clear is used to flag the light as clear
		* 
	*/

struct lightParams{
	GLenum lightNumber;
	GLfloat specular[4];
	GLfloat ambient[4]; 
	GLfloat diffuse[4]; 

	GLfloat position[4];
	GLfloat direction[3];
	GLfloat cutoff;
	bool active;//turn on or off the light
	bool clear;//delete the light to make a new one(set to true for clear)


};

class LightEngine{
public:
	LightEngine();

	/**
		*@brief Instance
		*
		* This returns a pointer to the singleton
		* 
		*@param nil
		*@returns LightEngine*
		*@post returns LightEngine singleton
	*/
	static LightEngine * Instance();

	/**
		*@brief Initialise
		*
		* This function initialises the Light Engine, it MUST be called in the GameEngine or input wont work.
		* 
		*@returns nil
		*@post sets up Input Engine
	*/
	void Initialise();

	/**
		*@brief createLight
		*
		* This function creates a light to be rendered
		* wont create a light if there is no lights available
		* returns -1 if there are no lights else it will return the value of the light in the array
		* 
		*@param Vec3 ambient, Vec3 specular, Vec3 Diffuse, Vec3 position, Vec3 Direction, GLfloat cutoff
		*@returns light ID number - int
		*@post creates a light for rendering
	*/
	int createLight(Vec3 ambient, Vec3 specular, Vec3 Diffuse, Vec3 position, Vec3 Direction, GLfloat cutoff);

	/**
		*@brief drawLights
		*
		* iterates through the array of lights and renders them on openGL
		* 
		*@param nil
		*@returns nil
		*@post renders all lights
	*/
	void drawLights();

private:
	/**
		*@brief getLightGlenum
		*
		* Takes an int value and turns it into Light0-Light7
		* 
		*@param int number
		*@returns Glenum - Light0 - Light7
		*@post creates a light for rendering
	*/
	GLenum getLightGlenum(int number);

	/// lightCount - int
	int lightCount;

	/// lightArray - lightParams
	lightParams lightArray[8];
};


#endif