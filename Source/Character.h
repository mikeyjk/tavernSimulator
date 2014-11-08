#pragma once

/**
	*@class Character
	*@brief The Character Class, the main controller that the user of a game would see.
	*@author:  Karl Tysoe, Liu Yi
	*@inherits:  GameObject
	*@date 26/03/2014
	*
*/

#include "GameObject.h"
#include  "Physic\Bbox.h"
#include "OpenGL.h"
#include "RenderingEngine.h"
#include "InputEngine.h"
#include "ControlSystem.h"
#include <iostream>
#include "Physic\PhysicalWorldSimulation.h"


using namespace std;

class InputEngine;
class Terrain;
class Character : public GameObject
{
public:
	/**
		*@brief Chracter Constructor
		*
		* This is the basic Constructor
		* Contructor chains with GameObject
		* gets a poitner to the input engine
		* 
		*@param RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture
		*@returns nil
	*/
	Character(RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture, bool bound, std::vector<Affordance> affordances);

	/**
		*@brief Chracter Destructor
		*
		* This is the basic Destructor
		* 
		*@param mil
		*@returns nil
	*/
	~Character(void);

	/**
		*@brief setTerrain Function
		*
		* This sets the terrain pointer to the one provided
		* 
		*@param Terrain* ter
		*@returns nil
	*/
	void setTerrain(Terrain* ter);

	/**
		*@brief i_DrawableObject Draw
		*
		* This calls the render engine funciton to draw a box
		* 
		*@param nil
		*@returns nil
	*/
	void Draw();

	/**
		*@brief i_DrawableObject SetBufferRef
		*
		* This sends the object to the renderEngine render buffer
		* 
		*@param nil
		*@returns nil
	*/
	void SetBufferRef();

	/**
		*@brief i_DrawableObject Destroy
		*
		* This deletes the object from the renderEngine buffer
		* 
		*@param nil
		*@returns nil
	*/
	void Destory();

	/**
		*@brief Update
		*
		* This is the character control function
		* 
		*@param nil
		*@returns nil
	*/
	virtual void Update(double deltaTime);

	void PickObject();
	
	bool canPick;

	cyclone::CollisionPrimitive * pickedObj;
	Bbox * body;

private:

	///pointer to the input engine
	InputEngine * input;
	//Collision dection for Physic Engine

	ControlSystem* control;
	

};

