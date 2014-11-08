#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

/**
	*@class ControlSystem
	*@brief The Class that the user of the system programs into directly for the creation of thier game,
	*       Basically this is the Control system, that is separated from character control.
	*@author:  Karl Tysoe
	*@inherits:  null
	*@Used By:  Game Engine;    
	*@date 26/03/2014
	*
*/

#include "InputEngine.h"
#include "RenderingEngine.h"
#include "HUD.h"



enum GameStatus
{
	GAME_RUN,
	GAME_STOP,
	GAME_EXIT
};

class ControlSystem
{
public:

	/**
		*@brief ControlSystem Destructor
		*
		* This is the basic Destructor
		* 
		*@param nil
		*@returns nil
	*/
	~ControlSystem(){};

	/**
		*@brief Instance
		*
		* Returns a pointer to a singleton of the object
		* 
		*@param nil
		*@returns nil
	*/
	static ControlSystem* Instance();
	
	/**
		*@brief init Function
		*
		* This function sets up all the pointers inside the ControlSystem
		* 
		*@param nil
		*@returns nil
	*/
	void init();

	/**
		*@brief Update Function
		*
		* This is the update Function
		* It is called every frame by the GameEngine
		* 
		*@param nil
		*@returns nil
	*/
	void Update(double deltaTime);

	void setStatus(GameStatus gs);
	GameStatus getStatus();

	/// Heads Up Display object
	HUD hud;

	int getHarvestTime(){return harvestTime;}


private:

	/**
		*@brief ControlSystem Constructor
		*
		* This is the basic Constructor
		* 
		*@param nil
		*@returns nil
	*/
	ControlSystem(){};
	
	///pointer to the input engine
	InputEngine * input;

	///pointer to the render engine
	RenderingEngine* render;

	
	GameStatus status;

	int harvestTime;

	bool playerDead;
};

#endif