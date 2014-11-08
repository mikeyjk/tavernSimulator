#include "MenuContainer.h"
#include "RenderingEngine.h"
#include "OpenGL.h"
#include "MenuButton.h"

MenuContainer::MenuContainer(float x, float y, float w, float h, string t)
	:MenuComponent(x,y,w,h,t)
{
}

void MenuContainer::checkPressedButton(float x,float y)
{
	if( posX < x && x <(posX+sizeW) && posY < y && y< (posY+sizeH))
	{
		for(int i=0;i < childs.size();i++)
		{
			childs[i]->checkPressedButton(x,y);
		}
	}
}

void MenuContainer::Draw()
{
	for(int i=0;i < childs.size();i++)
	{
		childs[i]->Draw();
	}
	((OpenGL *)RenderingEngine::Instance()->GetRenderHandle())->RenderOverlay(posX,posY,sizeW,sizeH,texture);
}

void MenuContainer::addChild(MenuComponent* child)
{
	childs.push_back(child);
}