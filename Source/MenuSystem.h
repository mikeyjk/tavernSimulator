#pragma once
#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <map>
#include "MenuContainer.h"
#include "MenuButton.h"
#include "I_DrawableObject.h"

using namespace std;
	
	/**
	 * @class MenuSystem
	 * @brief The MenuSystem class provide menu generation and managing methods
	 * @author Fang Xiang
	 * @date 026/05/2014
	 * @inherit I_DrawableObject
	 */
class MenuSystem : public I_DrawableObject
{
public:
	/**
	 * @brief Instance function
	 *
	 *	This function returns the singleton instance of the menu system
	 *
	 * @param nil
	 * @return MenuSystem* - this
	 */
	static MenuSystem* Instance();

	/**
	 * @brief switchMenu function
	 *
	 *	This function for turning on of turning off the menu
	 *
	 * @param nil
	 */
	static void switchMenu();

	/**
	 * @brief openMenu function
	 *
	 *	This function for turning on the menu
	 *
	 * @param nil
	 */
	static void openMenu();

	/**
	 * @brief closeMenu function
	 *
	 *	This function for turning off the menu
	 *
	 * @param nil
	 */
	static void closeMenu();
	
	/**
	 * @brief the draw function of the menu
	 *
	 * @param nil
	 */
	virtual void Draw();

	/**
	 * @brief checkPressedButton function
	 *
	 *	This function for checking is there a button be pressed, if do,
	 *	regist the button to the system, and show the button's pressed texture
	 *
	 * @param Vec2 - mouse position
	 */
	void checkPressedButton(Vec2 pos);

	/**
	 * @brief setPressedButton function
	 *
	 *	This function for registry of pressed button
	 *
	 * @param MenuButton* - reference of the pressed button
	 */
	void setPressedButton(MenuButton* button);

	/**
	 * @brief unpressButton function
	 *
	 *	This function for release the pressed function by change it's texture to the normal one,
	 *  whielst call the function bounded to this button
	 *
	 * @param Vec2 - mouse position
	 */
	void unpressButton(Vec2 pos);

	/**
	 * @brief SetBufferRef function
	 *
	 * rebuild function inherit from I_DrawableObject
	 *
	 * @param nil
	 */
	virtual void SetBufferRef();

	/**
	 * @brief Destory function
	 *
	 * rebuild function inherit from I_DrawableObject
	 *
	 * @param nil
	 */
	virtual void Destory();

	/**
	 * @brief MenuInit function
	 *
	 * Initialization of the menu
	 *
	 * @param nil
	 */
	void MenuInit();

	/**
	 * @brief MenuDisplay function
	 *
	 * active the menu component that will be viewed on the screen
	 *
	 * @param string - name of the component
	 */
	void MenuDisplay(string name);

	/**
	 * @brief newContainer function
	 *
	 * implement and regist menu container to the system
	 *
	 * @param name - name of the component
	 * @param x - position x
	 * @param y - position y
	 * @param w - width
	 * @param y - height
	 * @param t - texture name
	 * @return MenuContainer* - reference of the container
	 */
	MenuContainer* newContainer(string name, float x, float y, float w, float h, string t);

	/**
	 * @brief newButton function
	 *
	 * implement and regist menu button to the system
	 *
	 * @param name - name of the component
	 * @param x - position x
	 * @param y - position y
	 * @param w - width
	 * @param y - height
	 * @param t - texture name
	 * @param dt - name of pressed button texture
	 * @return MenuButton* - reference of the button
	 */
	MenuButton* newButton(string name, float x, float y, float w, float h, string t, string dt);

	/**
	 * @brief getComponent function
	 *
	 * get the reference of a menu component
	 *
	 * @param string - name of the component
	 * @return MenuComponent* - the reference
	 */
	MenuComponent* getComponent(string name);

	/**
	 * @brief desturcture funtion
	 */
	~MenuSystem();
private:
	MenuSystem();

	///component for viewing
	MenuComponent* displayer;

	///buffer for storing which button is pressed
	MenuButton* pressedButton;

	///bool value for viewing the menu
	bool showMenu;

	///map for storing references of all menu components registed to the system
	map<string,MenuComponent*> components;

	unsigned char m_objectID;
};
#endif