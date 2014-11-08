#ifndef GEOMETRY_H
#define GEOMETRY_H

/**
	*@class Geometry
	*@brief The Geometry Class, Basically static renderable objects
	*		The class doesnt need to update at the moment, so its just a static object
	*@author:  Karl Tysoe
	*@inherits:  GameObject
	*@date 11/04/2014
	*
*/

#include "GameObject.h"


class Geometry : public GameObject
{
public:
	/**
		*@brief Geometry Constructor
		*
		* This is the basic Constructor
		* 
		*@param nil
		*@returns nil
	*/
	Geometry(){type = gameObjectType::gameObject;}

	/**
		*@brief Geometry Constructor
		*
		* This is the basic parameter constructor
		* Contructor chains with GameObject
		* gets a poitner to the input engine
		* 
		*@param RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture
		*@returns nil
	*/
	Geometry(RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture, bool bound, float transparency, std::vector<Affordance> affordances,float weight);
	
	/**
		*@brief Geometry Destructor
		*
		* this is the basic destructor of the Geometry object
		* 
		*@param nil
		*@returns nil
	*/
	~Geometry(){}

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

	void Update(double deltaTime);

	void addSubModel(RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture, bool bound, float transparency);

	void addSubModel(Geometry* sub)
	{
		subModel = sub;
	}

	// void setTransparency(float t){trans = t;}

private:

	Geometry* subModel;
	
};


#endif GEOMETRY_H