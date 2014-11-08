#pragma once
#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "MenuComponent.h"

typedef void (*listener)();

	/**
	 * @class MenuButton
	 * @brief The MenuButton class is menu button
	 * @author Fang Xiang
	 * @date 026/05/2014
	 * @inherit MenuComponent
	 */
class MenuButton: public MenuComponent
{
public:
	/**
	 * @brief structure function
	 * @param x - position x
	 * @param y - position y
	 * @param w - width
	 * @param y - height
	 * @param t - texture name
	 * @param dt - name of pressed button texture
	 */
	MenuButton(float x, float y, float w, float h, string t, string dt);

	/**
	 * @brief draw function inherit from menu component
	 */
	void Draw();

	/**
	 * @brief Active function
	 * 
	 *	function for calling the bounded function with this button when its pressed
	 *
	 * @param x,y - mouse position
	 */
	void Active(float x,float y);

	/**
	 * @brief addListener function
	 * 
	 *	function for registing function to this button 
	 *
	 * @param l - callback function 
	 */
	void addListener(listener l);

	/**
	 * @brief checkPressedButton function
	 *	
	 *	inherit from menu component for check if buttons are pressed
	 *
	 * @param x,y - mouse position
	 */
	void checkPressedButton(float x,float y);

	/**
	 * @brief popUp function
	 *	
	 *	change the button's texture to its original 
	 */
	void popUp();

	/**
	 * @brief set the pressed texture of the button
	 *
	 * @param s - name of the string 
	 */
	void setDTexture(string s);

private:
	///reference of callback function
	listener func;
	///name of the original texture
	string upTexture;
	///name of the pressed texture
	string downTexture;
};
#endif