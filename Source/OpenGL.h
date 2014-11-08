#ifndef OPENGL_H
#define OPENGL_H

// #define GLM_FORCE_RADIANS

#include "I_Graphic.h"
#include "I_DrawableObject.h"
#include "GL\freeglut.h"
#include "Vec3.h"
#include <map>
#include <vector>
#include "Camera.h"
#include "InputEngine.h"
#include <string>

/**
	*@class OpenGL
	*@brief Implement all OpenGL API
	*@author:  Liu Yi
	*@inherits:  I_Graphic
	*@Used By:  RenderingFactory;    
	*@date 3/12/2014
	*
*/

using std::vector;
using std::map;
using std::string;
//class GameEngine;
class OpenGL;
static OpenGL * CurrentInstance;
static float gridSize = 520; // 520 by 520

class OpenGL : public I_Graphic 
{
	public:

	    OpenGL(void);
	
		~OpenGL(void);

		/**
			*@brief Initialization OpenGL
			*
			* This function do all the OpenGL set up;
			* 
			*@param void
			*@post Set up OpenGL API
		*/
	    void Init(int & argc, char ** argv, int Windowswidth, int WindowsHeight, char * name);

		/**
		*@brief Add the reference of Object to OpenGL Drawing list
		*
		* Add the pointer of object to internal Rendering buffer
		* 
		*@param void
		*@post Add the pointer into Rendering buff
	    */
		void AddRefToBuffer(int Id, I_DrawableObject * Ref);

		void DrawGrid(int size);

		/**
			*@brief Erase the reference of Object to OpenGL Drawing list
			*
			* Erase the pointer of object from internal Rendering buffer
			* 
			*@param void
			*@post Remove the pointer into Rendering buff
		*/
		void EraseRefFromBuffer(unsigned int);

		/**
			*@brief Let OpenGL Draw
			*
			* This function do all the OpenGL set up;
			* 
			*@param void
			*@post Set up OpenGL API
		*/
		void DrawModel(Vec3 Position);

		
		/**
		*@brief Reset OpenGL look at function 
		*
		*  Reset new value to glLookat
		* 
		*@param void
		*@post Update glLookat
	    */
		void CreateLookat();

		Camera * GetCamera() {return myCamera;}

		/**
		*@brief DrawSphere
		*
		* This function will Draw Sphere on the Screen
		* 
		*@param void
		*@post 
	    */
		void DrawSphere(Vec3 Position);

	   /**
		*@brief DrawTerrian
		*
		* DrawTerrian
		* 
		*@param void
		*@post 
	    */
		void DrawTerrian(Vec3 Position, std::string texturename, std::string DetailMap,GLuint elementbuffer,GLuint vetexbuffer,GLuint colorBuffer,GLuint TextureCoorbuffer, GLuint TextureCoorbufferDetail,int sizeofVertex,int sizeofColor, int sizeofTextureCoor, int sizeofMap, bool WireModel);
		
		/**
		*@brief RenderOverlay
		*
		* RenderOverlay
		* 
		*@param void
		*@post 
	    */
		void RenderOverlay(float start_x, float start_y,float w, float h, string name);

		/**
		*@brief Draw Model
		*
		* Draw Model
		* 
		*@param void
		*@post 
	    */
		void DrawModel(string ModelName,string TextureName,  float transparency , Vec3 transition, Vec3 rotation);

	   /**
		*@brief Draw Model
		*
		* Draw Model
		* 
		*@param void
		*@post 
	    */
		void DrawModel(string ModelName, string TextureName, float transparency, Vec3 transition, Vec3 rotation, Vec3 scale);

	   /**
		*@brief SetCallBackProcess
		*
		* SetCallBackProcess
		* 
		*@param void
		*@post 
	    */
		void SetCallBackProcess(void (*Process)(double));

		/**
		*@brief setFog
		*
		* set Fog
		* 
		*@param void
		*@post 
	    */
		void setFog(GLfloat start, GLfloat end);
		

	   /**
		*@brief render String
		*
		* render String
		* 
		*@param void
		*@post 
	    */
		void renderString(float start_x, float start_y, std::string text, int TextSize);

		void DrawSkyBox(Vec3 Center, GLuint vetexbuffer, GLuint elementbuffer, GLuint TextureCoorbuffer, string TextureName);

		void loop();

	private:
	
		map<int,I_DrawableObject*> RenderBuff;
		Camera * myCamera;
		InputEngine * myInput;

		void (*Process)(double);

		int WindowsWidth;
		int WindowsHeight;

		float differentX;
		float differentY;
		float LastX;
		float LastY;

		bool fogEnbled;

		//bool fixedMouse;

		//Need to declare all function as static

		/**
			*@brief This function will be called when you resize the Windows
			*
			* This function will Resize the Window
			* 
			*@param void
			*@post Resize the window
		*/
		  static void Resize(int w, int h); 




		   /**
			*@brief This function will be called when OpenGl draw frame
			*
			* This function will draw the frame on Screen
			* 
			*@param void
			*@post Draw object on Screen
		*/
		  static void Draw(); 


		  /**
			*@brief Update every frame
			*
			* This function should be call for every frame
			* 
			*@param void
			*@post Update the frame on Screen
		*/
		 static void Update(int value);


		 /**
			*@brief keyboardfunction
			*
			* Detect Keyboard function
			* 
			*@param void
			*@post
		*/
		 static void KeyBoardFun(unsigned char key, int x, int y);


	 		 /**
			*@brief keyboard up function
			*
			* Detect Keyboard up function
			* 
			*@param void
			*@post key up
		*/
		 static void KeyBoardUpFun(unsigned char key, int x, int y);





		  /**
			*@brief Mouse Click function
			*
			* Detect mouse Click
			* 
			*@param void
			*@post
		*/
		 static void mouseClickFunction(int button, int state, int x, int y);


		  /**
			*@brief Mouse Move function
			*
			* Detect mouse Click
			* 
			*@param void
			*@post
		*/
		 static void mouseMove(int x, int y);

};

#endif // OPENGL