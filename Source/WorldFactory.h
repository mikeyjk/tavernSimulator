#pragma once

/**
	*@class WorldFactory
	*@brief The Factory class that creates all GameObjects
	*@author:  Karl Tysoe, Liu Yi
	*@inherits:  nil
	*@date 26/03/2014
	*
*/

#include "GameObject.h"
#include "Geometry.h"
#include "Character.h"
#include "NPC.h"
#include "SkyBox.h"

class WorldFactory
{
public:
	/**
		*@brief WorldFactory Constructor
		*
		* This is the basic Constructor
		* 
		*@param nil
		*@returns nil
	*/
	WorldFactory(void);

	/**
		*@brief WorldFactory Destructor
		*
		* This is the basic Destructor
		* 
		*@param nil
		*@returns nil
	*/
	~WorldFactory(void);

	/**
		*@brief CreateObject function
		*
		* This creates an object of the name specified at the position specified, and sets the model and texture to the object
		* GameObject Types are: Character, Geometry, NPC, OtherPlayer, Terrain
		* 
		*@param string name, Vec3 Pos, string model, string texture
		*@returns GameObject* 
	*/
	GameObject* CreateObject(string name, Vec3 Pos, float rotX, float rotY, string model, string texture, bool bound, float transparency, float weight, std::vector<Affordance> affordances, std::vector<std::string> traits);

private:
	/// a pointer to the rendering engine
	RenderingEngine * rederingEngine;
};

