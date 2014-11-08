#ifndef NPC_H
#define NPC_H

#include "GameObject.h"
#include "Physic\Bbox.h"
#include "OpenGL.h"
#include "StateMachine.h"
#include "AIOwnedStates.h"
#include "RenderingEngine.h"
#include "ControlSystem.h"
#include "Physic\PhysicalWorldSimulation.h"
#include "Brain.h"

class InputEngine;
class Terrain;

/**
	*@class NPC / AI / Agent Class
	*@brief NPC Class. Defines non playable character / artifically intelligent agents.
	*@author: Michael J. Kiernan
	*@inherits: GameObject
	*@date 21/09/2014
*/
class NPC : public GameObject
{
	public:

		/**
		*@brief NPC ctor.
		*@param RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture
		*/
		NPC(RenderingEngine* Ref, Vec3 pos, float rotX, float rotY, 
			string model, string texture, bool bound, std::vector<Affordance> affordances, std::vector<std::string> traits,float weight);

		/**
		*@brief NPC dtor..
		*/
		~NPC();

		/**
		*@brief setTerrain Function
		*@param Terrain* ter
		*@returns nil
		*/
		void setTerrain(Terrain* ter);

		StateMachine<NPC>* GetFSM() const;

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
		void Update(double deltaTime);

		void changeState(State<NPC>& newState);

		void previousState(State<NPC>& newState);

		bool canPick;

		cyclone::CollisionPrimitive * pickedObj;

		void giveHudData()
		{
			myBrain.giveHudData();
			ControlSystem::Instance()->hud.giveHudAffordance(m_affordances);
		}

		void giveHudMoreData() { myBrain.giveHudMoreData(getID(), m_stateMachine->GetNameOfCurrentState()); }

		std::vector<Tag> getNeeds() {return(myBrain.getNeeds());}

		std::map<int, GameObject*> m_getAllCollidable;

		std::map<int, NPC*> m_getAllNPC;

		std::vector<GameObject*> getLocalAffordances();

		float getSpeed() { return myBrain.getSpeed(); }

		std::string getState();

		Brain* getBrain(){return &myBrain;}

		StateMachine<NPC>* getStatemachine(){return m_stateMachine;}

		PhysicalWorldSimulation* m_ps;

		Bbox * body;

	private:

		// Collision detection for the Physics Engine

		/// finite state machine
		StateMachine<NPC>* m_stateMachine;

		// a vector which gets populated by World
		// std::vector<int> m_localAffordances;

		// location
		Brain myBrain;
};

#endif // NPC_H