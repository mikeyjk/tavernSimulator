#ifndef BRAIN_H
#define BRAIN_H

/**
		* @class Brain
		* @brief This class contains the personality and connection to the affordance system
		*		The purpose of it is to abstract the gameObjects from decision making
		*		Has encapsulated functions of personality simply to give access
		* 
		* @todo: Fully break off affordance System from NPC (Eyes class?)
		* @author Karl, Michael
		* @version 01
		* @date 15/10/2014
     */


#include "Personality.h"
#include <vector>
#include "GameObject.h"
#include "AIOwnedStates.h"

class Brain
{
public:
	/**
		*@brief Brain constructor
		*
		* This constructor just sets the timer to 0, and the neeeds to 0
		*@param nil
		*@returns nil
	*/
	Brain();

	/**
		*@brief Brain destructor
		*
		* This destructor of the brain
		*@param nil
		*@returns nil
	*/
	~Brain();

	/**
		*@brief initPersonality function
		*
		* This takes in 4 string values (traits) and calls the addTrait on personality
		*@param std::string tr1, std::string tr2, std::string tr3, std::string tr4
		*@returns nil
	*/
	void initPersonality(std::string tr1, std::string tr2, std::string tr3, std::string tr4);


	/**
		*@brief update function
		*
		* Every 5 seconds the update function checks if there are any needs
		*@param double - deltaTime
		*@returns nil
	*/
	void update(double deltaTime);

	/**
		*@brief addTrait function
		*
		* Wrapper for Personality addTrait
		*@param tr string
		*@returns nil
	*/
	void addTrait(std::string tr);

	/**
		*@brief setState function
		*
		* This function will be called by brain to set the state
		* Dont think its needed because affordance isnt abstracted from NPC
		*@param nil
		*@returns nil
	*/
	void setState();

	/**
		*@brief getSight function
		*
		* wrapper for personality getSight
		*@param nil
		*@returns sight float
	*/
	float getSight() { return(PS->getSight());}

	/**
		*@brief giveHudData function
		*
		* wrapper for personality giveHudData function
		*@param nil
		*@returns nil
	*/
	void giveHudData()
	{
		PS->giveHudData();
	}

	/**
		*@brief giveHudModeData function
		*
		* wrapper for personality giveHudData function
		* passes in some data from NPC class
		*@param int npcid, std::string stateName
		*@returns nil
	*/
	void giveHudMoreData(int npcid, std::string stateName)
	{
		std::vector<int> ids;

		for(auto& aff : affordanceObjects)
		{
			ids.push_back(aff->getID());
		}

		PS->giveHudMoreData(npcid, stateName, getNeedsStr(), ids);
	}

	/**
		*@brief getNeeds function
		*
		* returns the needs that the brain has identified
		*@param nil
		*@returns vector<Tag> m_needs
	*/
	std::vector<Tag> getNeeds() { return(m_needs); }

	/**
		*@brief getNeedsStr function
		*
		* returns the needs that the brain has identified in vector string form
		*@param nil
		*@returns vector<string> m_needs
	*/
	std::vector<std::string> getNeedsStr();

	/**
		*@brief giveAffordancesThatMeetNeeds function
		*
		* function that gives the brain the affordance objects that it can compare to its needs.
		*@param vector<GameObject*> 
		*@returns nil
	*/
	void giveAffordancesThatMeetNeeds(vector<GameObject*> aff);

	bool ExternalStimuli(Tag name, float f, float tox = 0);

	/**
		*@brief getSpede function
		*
		* wrapper for personality getSpeed function
		*@param nil
		*@returns nil
	*/
	float getSpeed(){return PS->getSpeed();}

	/**
		*@brief calculateTarget function
		*
		* This functon does some simple comparisons and figues out what target is the best choice to go after
		* it also sets a tag for the NPC to transition into the correct state.
		*@param Tag &findState
		*@returns GGameObject* target
		*@post sets the findState Tag to the need (so the state machine can transition)
	*/
	GameObject* calculateTarget(Tag &findState);

	private:
	
		/// personality member object
		Personality* PS;
	
		/// simple timer double
		double queryTimer;

		///vector of needs that the personality returns and the brain can compare with
		std::vector<Tag> m_needs;

		/// vector of affordance gameObejcts that the brain can use to compare with to find a target.
		vector<GameObject*> affordanceObjects;
};

#endif