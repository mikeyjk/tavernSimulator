#include "MenuComponent.h"
#include "TextureManager.h"
#include "RenderingEngine.h"

MenuComponent::MenuComponent()
{
	posY = 0;
	posX = 0;
	sizeW = 0;
	sizeH = 0;
	texture = "";
}

MenuComponent::MenuComponent(float x, float y, float w, float h, string t)
{
	posY = y;
	posX = x;
	sizeW = w;
	sizeH = h;
	texture = t;
}

void MenuComponent::setTexture(string t)
{
	texture = t;
}