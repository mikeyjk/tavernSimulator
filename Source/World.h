#ifndef WORLD_H
#define WORLD_H

#include "RenderingEngine.h"
#include "WorldFactory.h"
#include "Global_Structs.h"
#include <vector>
#include <map>

/**
	*@class GameObject
	*@brief The GameWorld class is basically the Entity Management class
	*@author:  Liu Yi, Karl Tysoe
	*@date 26/03/2014
	*
	*@edit Michael J. Kiernam 13/09/2014
	* Refactored GameWorld -> World.
	* Removed pragma, introduced include guards.
	* Changed indenting.
	*
*/
class World
{
	public:
	
		/**
			*@brief Instance
			*
			* Returns a static pointer to the World object.
			* 
			*@returns World* object.
		*/
		static World* Instance();

		/**
			*@brief DeleteEntity
			*
			* Deletes an entity in the world by its unique identifier.
			* 
			*@param int entity identifier
		*/
		 void DeleteEntity(int entityId);

		/**
			*@brief addEntity function
			*
			* This function adds an entity to the gameWorld class
			* The string determines what entity you can add, the \
			*  different types of entities are: NPC, Terrain, Geometry, \
			*  Character, OtherPlayer.
			* These entities are added to the GameWorld maps and are then \
			*  have thier update called every frame.
			* Also this function adds the models and textures to the Resource Manager, \
			*  if they havent previously been added.
			* 
			*@param string name, Vec3 pos, float rotX, float rotY, \
			*  string model, string texture, bool bound, float transparency
			*@returns GameObject* 
		*/
		GameObject* AddEntity(string name, Vec3 pos, float rotX, float rotY, string model, 
			string texture, bool bound, float transparency, float weight, std::vector<Affordance> affordances, std::vector<std::string> traits);

		GameObject* GetCollisionEntity(int entityId);

		GameObject* GetNoCollisionEntiy(int entityId);

		/**
			*@brief getChar function
			*
			* This returns the Character pointer for the mainCharacter
			* 
			*@param nil
			*@returns MainCharacter - Character*
		*/
		Character* GetMainCharacter();

		/**
			*@brief update
			*
			* This function is called by the GameEngine at every frame
			* Calls the update function for every entity.
			* 
		*/
		void Update(double deltaTime);

		void AddSkybox();

		std::map<int, GameObject*> getCollidableEntities()
		{
			return m_collisionEntities;
		}

		std::map<int, GameObject*> getNonCollidableEntities()
		{
			return m_nonCollisionEntities;
		}

	private:

		/**
			*@brief World Constructor
			*
			* Private World constructor.
			* Not able to be invoked directly.
		*/
		explicit World();

		RenderingEngine* m_renderingHandle;

		bool m_mainCharacter; // reference to character object

		std::vector<int> m_npcShortCut;

		SkyBox* m_skybox; // reference to skybox object

		WorldFactory m_worldFactory; // use to create a static instance of 'World'/this

		map<int, GameObject*> m_nonCollisionEntities; // non collidable entities

		map<int, GameObject*> m_collisionEntities;  // collidable entities
};

#endif // WORLD_H