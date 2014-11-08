#ifndef INPUT_ENGINE_H
#define INPUT_ENGINE_H

/**
	*@class InputEngine
	*@brief The Control of all input for the system, created as a singleton so that users will only ever use one instance.
	*@author:  Karl Tysoe
	*@inherits:  null
	*@date 26/03/2014
	*
*/

#include "GL\freeglut.h"
#include <string>

/**
		*@brief enum KeyCode
		*
		* KeyCode is the enumerator that determines what keyboard input the user wants to find out if it has been pressed
		* 
	*/
enum KeyCode
{
	A=0,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	Alpha1,Alpha2,Alpha3,Alpha4,Alpha5,Alpha6,Alpha7,Alpha8,Alpha9,Alpha0,

	//not sure if I want to include at this point in time.
	NumPad0, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
	NumPadDel, NumPadPlus, NumPadMinus, NumPadStar, NumPadSlash, NumLock, PrintScreen, ScrLock, PauseBreak,

	Space,
	Tilde,
	Dash,
	Equals,
	Backspace,
	Tab,
	CapsLock,
	BackSlash,
	Enter,
	OpenBracket,
	ClosedBracket,
	Colon,
	Apostrophe,
	Comma,
	Period,
	ForwardSlash,
	Delete,
	Esc,

	//All these keys are the "special" keys
	Ins, Home, End, PageUp, PageDown,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	LeftKey, UpKey, RightKey, DownKey,
	LeftShift, LeftCtrl, LeftAlt, RightShift, RightCtrl, RightAlt

};

/**
		*@brief enum MouseCode
		*
		* MouseCode is the enumerator that determines what Mouse input the user wants to find out if it has been pressed
		* 
	*/
enum MouseCode
{
	LeftClick = 0,
	MiddleClick = 1,
	RightClick = 2,
	ScrollUp = 3,
	ScrollDown = 4,
	PressedScrollUp = 35,
	PressedScrollDown = 36
};

struct Vec2//can be changed
{
	float x;
	float y;
};

class InputEngine
{
public:
	/**
		*@brief Instance
		*
		* This returns a pointer to the singleton
		* 
		*@param nil
		*@returns InputEngine*
		*@post returns InputEngine singleton
	*/
	static InputEngine* Instance();

	/**
		*@brief initInputControl
		*
		* This function initialises the Input Engine, it MUST be called in the GameEngine or input wont work.
		* The string determines weather the engine uses openGL or DirectX
		* 
		*@param string - type
		*@returns nil
		*@post sets up Input Engine
	*/
	void initInputControl(std::string type);

	 

	 /**
		*@brief Set Mouse Fixed
		*
		* This sets the boolean value for Fixed Mouse
		* 
		*@param bool - fix
		*@returns nil
		*@post sets FixedMouse to fix
	*/
	 void setMouseFixed(bool fix);

	 /**
		*@brief Get Mouse Fixed
		*
		* This returns the boolean value for fixedMouse
		* Used to determine if the user wants the cursor to be free moving or not.
		* 
		*@param nil
		*@returns FixedMouse - Bool
		*@post returns FixedMouse
	*/
	 bool getMouseFixed();

	 /**
		*@brief Reset All Keys
		*
		* This resets all mouseDown, MouseUP, KeyDown and KeyUp arrays to false.
		* must be called after the inputs have been used, at the end of the game loop
		* 
		*@param nil
		*@post resets the arrays for input
	*/
	 void resetAllKeys();

	 /**
		*@brief Get Key Down
		*
		* Use the Keycode provided to check to see if that key has been pressed down in this frame.
		* This will only be true for the first frame of the down press.
		* 
		*@param KeyCode - key
		*@post returns true or false based on the keyCode provided
	*/
	 bool getKeyDown(KeyCode key);

	 /**
		*@brief Get Key
		*
		* Use the Keycode provided to check to see if that key is being pressed.
		* This will be true for the entire time the key is pressed.
		* 
		*@param KeyCode - key
		*@returns bool
		*@post returns true or false based on the keyCode provided
	*/
	 bool getKey(KeyCode key);

	 /**
		*@brief Get Key Up
		*
		* Use the Keycode provided to check to see if that key has been released in this frame.
		* This will only be true for the first one frame of key release
		* 
		*@param KeyCode - key
		*@returns bool
		*@post returns true or false based on the keyCode provided
	*/
	 bool getKeyUp(KeyCode key);

	 /**
		*@brief Get Mouse Down
		*
		* Use the MouseCode provided to check to see if that Mouse Button has been clicked down in this frame.
		* This will only be true for the first frame of the down press.
		* 
		*@param MouseCode - key
		*@returns bool
		*@post returns true or false based on the MouseCode provided
	*/
	 bool getMouseDown(MouseCode key);

	 /**
		*@brief Get Mouse
		*
		* Use the MouseCode provided to check to see if the Mouse Button is clicked down in this frame.
		* This will be true for the entire time of the down press.
		* 
		*@param MouseCode - key
		*@returns bool
		*@post returns true or false based on the MouseCode provided
	*/
	 bool getMouse(MouseCode key);

	 /**
		*@brief Get Mouse Up
		*
		* Use the MouseCode provided to check to see if that Mouse Button has been released in this frame.
		* This will only be true for the one frame of key release
		* 
		*@param MouseCode - key
		*@returns bool
		*@post returns true or false based on the MouseCode provided
	*/
	 bool getMouseUp(MouseCode key);

	 /**
		*@brief Get Mouse Point
		*
		* Get the Vec2 that contains the mouses current position
		* 
		*@param void
		*@returns bool
		*@post return a vec2 of the mouses current position
	*/
	 Vec2 getMousePoint();

	 /**
		*@brief Get Alpha Point
		*
		* Gets the difference between the last frames mouse positon and this position
		* 
		*@param void
		*@returns MousePosition - Vec2
		*@post return a Vec2 mouse point
	*/
	 Vec2 getAlphaMousePoint();

	 /**
		*@brief Set Cursor Mid
		*
		* Sets the cursor to be stuck at the middle of the screen
		* 
		*@param void
		*@returns AlphaMousePosition - Vec2
		*@post sets the cursor to mid of screen
	*/
	 void setCursorMid();

	 void switchFixedMouse();
	
private:

	/**
		*@brief keyPressed - static void
		*
		* Function for setting all the keyboard input through openGL.
		* Keyboard Down presses
		* Sets the bool arrays for keyPressed, KeyPressedDown
		* 
		*@param unsigned char key, int x, int y
		*@returns nil
	*/
	 static void keyPressed(unsigned char key, int x, int y);

	 /**
		*@brief keyUp - static void
		*
		* Function for setting all the keyboard input through openGL.
		* Keyboard releases
		* Sets the bool arrays for keyPressed, KeyPressedUp
		* 
		*@param unsigned char key, int x, int y
		*@returns nil
	*/
	 static void keyUp(unsigned char key, int x, int y);

	 /**
		*@brief SpecialFunc - static void
		*
		* Function for setting special keyboard input through openGL.
		* Keyboard down presses
		* Sets the bool arrays for keyPressed, KeyPressedDown
		* 
		*@param int char key, int x, int y
		*@returns nil
	*/
	 static void SpecialFunc(int key, int x, int y);

	  /**
		*@brief SpecialUpFunc - static void
		*
		* Function for setting special keyboard input through openGL.
		* Keyboard releases
		* Sets the bool arrays for keyPressed, KeyPressedUp
		* 
		*@param int char key, int x, int y
		*@returns nil
	*/
	 static void SpecialUpFunc(int key, int x, int y);

	  /**
		*@brief MouseMotion - static void
		*
		* Function for setting the Mouse point
		* sets the position that the user can get back from the Input Engine
		* sets the delta position of the mouse as well
		* 
		*@param int x, int y
		*@returns nil
	*/
	 static void MouseMotion(int x ,int y);

	 /**
		*@brief MouseFunction - static void
		*
		* Function for setting the Mouse button clicks and releases
		* sets mouseButtonDown on the first frame of a click
		* mouseButtons for the whole duration
		* and mouseButtonsUp on the first frame of release.
		* 
		*@param int button, int x, int y
		*@returns nil
	*/
	 static void MouseFunction(int button, int state, int x, int y) ;

	/**
		*@brief InputEngine Constructor
		*
		* Basic constructor of the Input Engine
		* 
		*@param nil
		*@returns nil
	*/
	InputEngine();

	/// Holds the position of the mouse at any frame it is called
	Vec2 mousePoint;

	/// This is the difference from last frame to this frame
	Vec2 alphaMousePoint;
	
	
	///this will only be true for the one frame that this key is Down
	bool keyStatesDown[256];
	///this will only be true for the one frame that this key is Down
	bool specialKeysDown[120];
	///this will only be true for the one frame that this key is Down
	bool mouseButtonsDown[5];

	///will be true when the button is down, false as soon as its up
	bool keyStates[256];
	///will be true when the button is down, false as soon as its up
	bool specialKeys[120];
	///will be true when the button is down, false as soon as its up
	bool mouseButtons[5];

	///will be true for the one frame that the button comes up, false all other times.
	bool keyStatesUp[256];
	///will be true for the one frame that the button comes up, false all other times.
	bool specialKeysUp[120];
	///will be true for the one frame that the button comes up, false all other times.
	bool mouseButtonsUp[5];

	/// this is used to determine if the user of the system wants to set the mouse point to be fixed and invisible
	bool fixedMouse;
};


#endif