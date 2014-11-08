#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "RenderingEngine.h"
#include "World.h"
#include "InputEngine.h"
#include "ControlSystem.h"
#include "MenuSystem.h"
#include "ResourceManager.h"
#include "LightEngine.h"
#include "Physic\PhysicEngine.h"

#include "Timer.h"

#include <boost/algorithm/string.hpp> // string split
#include <boost/lexical_cast.hpp> // string -> int/float

#include <cstring>
#include <string> // handling string objects
#include <vector> // storing file data
#include <fstream> // opening/reading files
#include <iterator> // std::distance
#include <iostream> // debug

using namespace boost; // boost namespace for string handling

class GameEngine;
static GameEngine * EngineInstance; 

/**
	*@Class GameEngine
	*@Brief The entry of the entire Engine
	*@Author: Liu Yi
	*@Inherits: null
	*@Used By: main;    
	*@Date 3/12/2014
	*
	*@Edit: 29/08/14 - Michael J. Kiernan
	*	- Added support for transparency and rotation
	*		when loading asset from file.
	*
	*@Edit: 27/08/14 - Michael J. Kiernan
	*	- Change from #pragma once to ifndef guard.
	*	- Removed includes from .cpp.
	*	- Added primitive asset loading from file.
	*
	*@Edit: 27/08/14 - Karl Tysoe
	*	- Added/testing LightEngine.
*/
class GameEngine
{
	public:
	
		  static GameEngine* instance();

			/**
				*@brief Get Redering engine
				*
				* Get the Pointer which point to Rendering engine
				* 
				*@param void
				*@post return a I_Graphic Pointer to the Rendering APi
			*/
		   void start(char *,int & argc, char ** argv, int Windowswidth, int WindowsHeight, char * name);
	
		  static void update(double deltaTime);

	private:

		/**
			*@brief GameEngine Constructor
			*
			* This basic constructor of the gameEngine
			* instantiates all the singleton objects
			* 
			*@param nil
			*@returns nil
		*/
		explicit GameEngine();

		/**
			*@brief GameEngine Destructor
			*
			* The basic destructor of the GameEngine
			* 
			*@param Vec3 pos
			*@returns nil
		*/
		~GameEngine(void);

		// pointer to the rendering engine
		RenderingEngine * myRenderingEngine;

		// pointer to the World
		World * myWorld;

		// pointer to the input Engine
		InputEngine * myInputEngine;

		// pointer to the gameSystem
		ControlSystem * myControlSystem;

		SoundManager* m_soundManager;

		MenuSystem * myMenuSystem;

		// location of text file that defines assets/objects
		std::string m_assetFile;

		PhysicEngine * myPhysicEngine;

		/**
		  * @Function loadAssets()
		  *	@Summary loads models/object data from file.
		  */
		void loadAssets();

		Timer* EngineTime;
};

#endif // GAMEENGINE_H