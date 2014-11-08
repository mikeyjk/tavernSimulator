#ifndef PHYSICALENGINE_H
#define PHYSICALENGINE_H

#include "PhysicalWorldSimulation.h"
#include "..\Camera.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace boost;

class PhysicEngine
{
	public:
			/**
			*@brief Singleton
			*
			* Create the singleton
			* 
		    */
		static PhysicEngine * Instance();

		~PhysicEngine(void);

			/**
			*@brief Update
			*
			* Update entire physic world
			* 
		    */
		void Update(double deltaTime);

		    /**
			*@brief loadAssets
			*
			* Load Assets from external file
			* 
		    */
		void loadAssets();

		    /**
			*@brief Draw
			*
			* Draw all elements in physic world
			* 
		    */
		void Draw();

		PhysicalWorldSimulation * WorldSimu;

		
		    /**
			*@brief switchRenderMode
			*
			* Draw or not draw
			* 
		    */
		void switchRenderMode(){renderBBoxes = !renderBBoxes;}


	
	private:
	
		PhysicEngine(void);

		// location of text file that defines assets/objects
		std::string m_assetFile;

		    /**
			*@brief add object
			*
			* add objects into world
			* 
		    */
		void addObjects();

		bool renderBBoxes;

};

#endif //PHYSICALENGINE_H