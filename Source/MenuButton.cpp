#include "MenuButton.h"
#include "MenuSystem.h"
#include "RenderingEngine.h"
#include "OpenGL.h"

MenuButton::MenuButton(float x, float y, float w, float h, string t, string dt)
	:MenuComponent(x,y,w,h,t)
{
	upTexture = t;
	downTexture = dt;
	func = NULL;
}

void MenuButton::Draw()
{
	((OpenGL *)RenderingEngine::Instance()->GetRenderHandle())->RenderOverlay(posX,posY,sizeW,sizeH,texture);
}

void MenuButton::addListener(listener l)
{
	func = l;
}

void MenuButton::Active(float x, float y)
{
	if( posX < x && x <(posX+sizeW) && posY < y && y< (posY+sizeH))
	{
		if(func != NULL)
			(*func)();
	}
}

void MenuButton::checkPressedButton(float x, float y)
{
	if( posX < x && x <(posX+sizeW) && posY < y && y< (posY+sizeH))
	{
		setTexture(downTexture);
		MenuSystem::Instance()->setPressedButton(this);
	}
}

void MenuButton::popUp()
{
	setTexture(upTexture);

}

void MenuButton::setDTexture(string s)
{
	downTexture = s;
}