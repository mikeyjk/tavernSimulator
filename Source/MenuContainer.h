#pragma once
#ifndef MENUCONTAINER_H
#define MENUCONTAINER_H

#include "MenuComponent.h"
#include <vector>
using namespace std;

	/**
	 * @class MenuContainer
	 * @brief The MenuContainer class is menu component for contain components and showing background
	 * @author Fang Xiang
	 * @date 026/05/2014
	 * @inherit MenuComponent
	 */
class MenuContainer: public MenuComponent
{
public:
	/**
	 * @brief structure function
	 * @param x - position x
	 * @param y - position y
	 * @param w - width
	 * @param y - height
	 * @param t - texture name
	 */
	MenuContainer(float x, float y, float w, float h, string t);

	/**
	 * @brief draw function inherit from menu component
	 */
	void Draw();

	/**
	 * @brief checkPressedButton function
	 *	
	 *	inherit from menu component for check if buttons are pressed
	 *
	 * @param x,y - mouse position
	 */
	void checkPressedButton(float x,float y);

	/**
	 * @brief addChild function
	 *	
	 *	put components under this container
	 *
	 * @param child - the component
	 */
	void addChild(MenuComponent* child);

private:
	///vector for storing references of components in this container
	vector<MenuComponent*> childs;
};
#endif