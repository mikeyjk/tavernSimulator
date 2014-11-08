#ifndef RenderingEngine_H
#define RenderingEngine_H

/**
	*@class Rendering Engine
	*@brief The entry of 3D rendering Engine
	*@author:  Liu Yi
	*@inherits:  null
	*@Used By:  GameEngine;    
	*@date 3/12/2014
	*
*/

#include "RederingFactory.h"
#include "OpenGL.h"

class RenderingEngine
{
	public:

	/**
		*@brief Create the Render API
		*
		* This function decide which API should be used, either OpenGL or DirectX11
		* 
		*@param string (either "OP" or "DX")
		*@post assign a Render object to Handle
	*/
	void CreateRenderAPI(string name);

	/**
		*@brief Get the Handle of Rendering API
		*
		* This function return the Handle of Rendering API
		* 
		*@param void
		*@post return a I_Graphic Pointer to the Rendering APi
	*/
	I_Graphic * GetRenderHandle();
	
	Camera * GetCamera();

	void AddRefToBuffer(int Id, I_DrawableObject * Ref);

	/**
	*@brief Erase the reference of Object to OpenGL Drawing list
	*
	* Erase the pointer of object from internal Rendering buffer
	* 
	*@param void
	*@post Remove the pointer into Rendering buff
	*/
	void EraseRefFromBuffer(unsigned int);

	void RenderOverlay(float start_x, float start_y,float w, float h,string name);

	void DrawModel(string ModelName, string TextureName, float transparency, Vec3 transition, Vec3 rotation);

	void DrawModel(string ModelName,string TextureName, float transparency, Vec3 transition, Vec3 rotation, Vec3 scale);

	static RenderingEngine* Instance();

private:

	//Handle the Version of rendering interface;
	I_Graphic * Handle;
	RederingFactory APIFactory;
	RenderingEngine(void);
	~RenderingEngine(void);
 
};


#endif