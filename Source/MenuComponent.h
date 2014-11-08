#pragma once
#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include <string>
#include "IdGenerator.h"
#include "InputEngine.h"


using namespace std;
	
	/**
	 * @class MenuComponent
	 * @brief The MenuComponent class is a parent class for components like buttons and panels
	 * @author Fang Xiang
	 * @date 026/05/2014
	 */
class MenuComponent
{
public:
	/**
	 * @brief structure function
	 */
	MenuComponent();

	/**
	 * @brief structure function
	 * @param x - position x
	 * @param y - position y
	 * @param w - width
	 * @param y - height
	 * @param t - texture name
	 */
	MenuComponent(float x, float y, float w, float h, string t);

	/**
	 * @brief virtual draw function
	 */
	virtual void Draw(){};

	/**
	 * @brief checkPressedButton function
	 *	
	 *	virtual function for check if buttons are pressed;
	 * @param x,y - mouse position
	 */
	virtual void checkPressedButton(float x,float y){};

	/**
	 * @brief set the texture of the component
	 *
	 * @param t - the texture
	 */
	void setTexture(string t);
protected:
	/// name of the texture
	string texture;
	/// width
	float sizeW;
	///height
	float sizeH;
	///position x
	float posX;
	///position y
	float posY;
	/// id for rendering engine for drawing
	unsigned int m_objectID;
};
#endif