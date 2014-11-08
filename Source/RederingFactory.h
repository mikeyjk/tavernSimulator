#pragma once

/**
	*@class RederingFactory
	*@brief Create the Rendering APi
	*@author:  Liu Yi
	*@inherits:  null
	*@Used By:  RenderingEngine    
	*@date 3/12/2014
	*
*/
#include <string>
#include <cassert>
#include "OpenGL.h"
#include "DirectX.h"


using std::string;

class RederingFactory
{
	

		

public:
	RederingFactory(void);
	~RederingFactory(void);


	/**
		*@brief Create the Render API
		*
		* This function decide which API should be used, either OpenGL or DirectX11
		* 
		*@param string (either "OP" or "DX")
		*@post return a I_Graphic Pointer to the Rendering APi
	*/
	I_Graphic * CreateRender(string name);


private:
	
};

