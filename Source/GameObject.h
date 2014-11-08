#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "Vec3.h"
#include "I_DrawableObject.h"
#include "IdGenerator.h"
#include "Physic\Bbox.h"
#include "ResourceManager.h"
#include "RenderingEngine.h"
#include "Global_Structs.h"
#include "Affordance.h"
#include "Traits.h"
#include "Physic\PhysicEngine.h"

class RenderingEngine;

enum gameObjectType // types of game objects
{
	gameObject = 0,
	character,
	geometry,
	npc
};

/**
	*@class GameObject
	*@brief The Parent class of all the entities in the Engine
	*@author: Karl Tysoe
	*@inherits: I_DrawableObject
	*@date 26/03/2014
	*
*/

class GameObject : public I_DrawableObject
{
	public:

		/**
			*@brief GameObject Constructor
			*
			* This is the basic Constructor
			* inisialises everything to 0
			* 
			*@param nil
			*@returns nil
		*/
		GameObject();

		/**
			*@brief GameObject Constructor
			*
			* This is the parameter Constructor
			* initialises or points to all parameters specified
			* 
			*@param RenderingEngine* ref, Vec3 pos, float rotX, float rotY, string model, string texture
			*@returns nil
			*@post Constructor chain with GameObject
		*/
		GameObject(RenderingEngine* ref, Vec3 pos, float rotX, float rotY, 
			std::string model, std::string texture, bool Isbound, float transparency, float weight);

		/**
			*@brief GameObject Destructor
			*
			* This is the Destructor
			* Sets all pointers to nullptr
			* 
			*@param nil
			*@returns nil
			*@post sets all pointers to null
		*/
		~GameObject();

		/**
			*@brief setPosition
			*
			* This sets the position with a vector provided
			* 
			*@param Vec3 - pos
			*@returns nil
			*@post sets position to pos
		*/
		void setPosition(Vec3 pos);

		/**
			*@brief setPosition
			*
			* This sets the position with the floats provided
			* 
			*@param float x, float y, float z
			*@returns nil
			*@post sets position to floats
		*/
		void setPosition(float x, float y, float z);

		/**
			*@brief getPosition
			*
			* basic getter for the position varialble
			* 
			*@param nil
			*@returns position - Vec3
		*/
		Vec3 getPos();

		/**
			*@brief SetRotation
			*
			* This sets the rotation for X and Y
			* Probably to be changed for Quaternion
			* 
			*@param float rotX, float rotY
			*@returns nil
			*@post sets rotations to once provided
		*/
		void setRotation(float rotX, float rotY, float rotZ);

		void setTransparency(float transparency){trans = transparency;};

		/**
			*@brief getRotationX
			*
			* basic getter for the rotationX varialble
			* 
			*@param nil
			*@returns rotationX - float
		*/
		float getRotationX();

		/**
			*@brief getRotationY
			*
			* basic getter for the rotationY varialble
			* 
			*@param nil
			*@returns rotationY - float
		*/
		float getRotationY();

		/**
			*@brief SetTexture
			*
			* This sets the texture name to the one provided
			* 
			*@param string tex
			*@returns nil
			*@post sets texture to tex
		*/
		void setTexture(std::string tex);

		/**
			*@brief SetModel
			*
			* This sets the model name to the one provided
			* 
			*@param string mod
			*@returns nil
			*@post sets model to mod
		*/
		void setModel(std::string mod);

		/**
			*@brief getTexture
			*
			* basic getter for the texture variable
			* 
			*@param nil
			*@returns texture - string
		*/
		std::string getTexture();

		/**
			*@brief getModel
			*
			* basic getter for the model variable
			* 
			*@param nil
			*@returns model - string
		*/
		std::string getModel();

		/**
			*@brief getID function
			*
			* The basic getter function for the GameObject ID
			* 
			*@param nil
			*@returns m_objectID - int
		*/
		int getID(){return m_objectID;}

		/**
			*@brief setObjectType function
			*
			* The basic setter for the enum for the gameObjectType
			* 
			*@param gameObjectType t
			*@returns nil
		*/
		void setObjectType(gameObjectType t){type = t;}

		/**
			*@brief getObjectType function
			*
			* The basic getter for the enum for the gameObjectType
			* 
			*@param nil
			*@returns type - gameObjectType
		*/
		gameObjectType getObjecType(){return type;}

		/**
			*@brief virtual i_DrawableObject Draw
			*
			* put here to make invisible GameObjects Possible
			* 
			*@param nil
			*@returns nil
		*/
		virtual void Draw(){}

		/**
			*@brief virtual i_DrawableObject SetBufferRef
			*
			* put here to make invisible GameObjects Possible
			* 
			*@param nil
			*@returns nil
		*/
		virtual void SetBufferRef(){}

		/**
			*@brief virtual i_DrawableObject Destroy
			*
			* put here to make invisible GameObjects Possible
			* 
			*@param nil
			*@returns nil
		*/
		virtual void Destory(){}

		/**
			*@brief virtual Update
			*
			* Put here to be able to call Update for all child GameObjects
			* 
			*@param nil
			*@returns nil
		*/
		virtual void Update(double deltaTime){}

		void setBBox();

		void setAffordances(std::vector<Affordance> affordances);

		Vec3 getRotation();

		std::vector<Affordance> getAffordances() const;

		void addAffordance(const Affordance newAffordance);

		void setBoundingPos(Vec3 p)
		{
			Bounding->body->setPosition(p.X, p.Y, p.Z);
			Bounding->body->calculateDerivedData();
	        Bounding->calculateInternals();
		}

		void setTargetObject(GameObject* t){targetObject = t;}

		GameObject* getTarget(){return targetObject;}

	protected:

		// pointer for the IDgenerator
		IdGenerator* IdGen;

		// pointer for the Render Engine
		RenderingEngine* RederingHandle;

		// enumerated type to identify what type of GameObject this is
		gameObjectType type;

		// unique game object identifier
		int m_objectID;

		// Position point(Vec3)
		Vec3 m_position;

		Vec3 m_rotation;

		/// texture string (used for getting the texture from the resourceManager)
		std::string texture;

		/// model string (used for getting the model from the resourceManager)
		std::string model;

		// transparency
		float trans;

		Bbox* Bounding;
	
		bool isBounding;

		// bounding boxes

		std::vector<Affordance> m_affordances;

		GameObject* targetObject;
};
#endif // GAMEOBJECT_H