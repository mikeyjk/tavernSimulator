#pragma once


/**
	*@class DirectX
	*@brief Implement all DirectX API
	*@author:  Liu Yi
	*@inherits:  I_Graphic
	*@Used By:  RenderingFactory;    
	*@date 3/12/2014
	*
*/


#include "I_Graphic.h"
class DirectX : public I_Graphic  
{
public:
	DirectX(void);
	~DirectX(void);

	/**
		*@brief Initialization OpenGL
		*
		* This function do all the Dx set up;
		* 
		*@param void
		*@post Set up Dx API
	*/
	void Init();




	/**
		*@brief Create the Window of Dx
		*
		* This function will Create the target window
		* 
		*@param void
		*@post Set up a window for Rendering
	*/



	/**
		*@brief Update every frame
		*
		* This function should be call for every frame
		* 
		*@param void
		*@post Update the frame on Screen
	*/
    void Update();


};

