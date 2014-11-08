#include "MenuSystem.h"
#include "IdGenerator.h"
#include "RenderingEngine.h"
#include "ControlSystem.h"
#include "TextureManager.h"
#include "GL\freeglut.h"

MenuSystem* MenuSystem::Instance()
{
	static MenuSystem* instance = new MenuSystem();
	return instance;
}

MenuSystem::MenuSystem()
{
	showMenu = true;
	pressedButton = NULL;
	m_objectID = IdGenerator::Instance()->GetID();
}

void MenuSystem::switchMenu()
{
	MenuSystem::Instance()->showMenu = !MenuSystem::Instance()->showMenu;
}

void MenuSystem::openMenu()
{
	MenuSystem::Instance()->showMenu = true;
}

void MenuSystem::closeMenu()
{
	MenuSystem::Instance()->showMenu = false;
}

void MenuSystem::Draw()
{
	if(MenuSystem::Instance()->showMenu)
		MenuSystem::Instance()->displayer->Draw();
}

void MenuSystem::setPressedButton(MenuButton* button)
{
	pressedButton = button;
}

void MenuSystem::unpressButton(Vec2 pos)
{
	if(pressedButton != NULL)
	{
		pressedButton->popUp();
		int window_W = glutGet(GLUT_WINDOW_WIDTH);
		int window_H = glutGet(GLUT_WINDOW_HEIGHT);
		int fixed_W = 1200;
		int fixed_H = 800;
		float x,y;
		x=(pos.x/ window_W) * fixed_W;
		y=((window_H - pos.y)/window_H) * fixed_H;
		pressedButton->Active(x,y);
	}
}

void MenuSystem::checkPressedButton(Vec2 pos)
{
	if(MenuSystem::Instance()->showMenu) {
		int window_W = glutGet(GLUT_WINDOW_WIDTH);
		int window_H = glutGet(GLUT_WINDOW_HEIGHT);
		int fixed_W = 1200;
		int fixed_H = 800;
		float x,y;
		x=(pos.x/ window_W) * fixed_W;
		y=((window_H - pos.y)/window_H) * fixed_H;
		MenuSystem::Instance()->displayer->checkPressedButton(x,y);
	}
}

void MenuSystem::MenuDisplay(string name)
{
	displayer = components[name];
}

MenuContainer* MenuSystem::newContainer(string name, float x, float y, float w, float h, string t)
{
	MenuContainer* component;
	component = new MenuContainer(x,y,w,h,t);
	components.insert(pair<string,MenuComponent*>(name,component));
	return component;
}

MenuButton* MenuSystem::newButton(string name, float x, float y, float w, float h, string t, string dt)
{
	MenuButton* component;
	component = new MenuButton(x,y,w,h,t,dt);
	components.insert(pair<string,MenuComponent*>(name,component));
	return component;
}

MenuComponent* MenuSystem::getComponent(string name)
{
	return components[name];
}

void resume()
{
	MenuSystem::Instance()->switchMenu();
	InputEngine::Instance()->switchFixedMouse();
	ControlSystem::Instance()->setStatus(GAME_RUN);
	MenuSystem::Instance()->getComponent("btn1")->setTexture("btn_rsm");
	((MenuButton*)MenuSystem::Instance()->getComponent("btn1"))->setDTexture("btn_rsm_d");
}

void showexit()
{
	ControlSystem::Instance()->setStatus(GAME_EXIT);
	MenuSystem::Instance()->MenuDisplay("thx");
}

void exit()
{
	glutLeaveMainLoop();
	glutExit();
	exit(0);
}

void MenuSystem::MenuInit()
{
	TextureManager::Instance()->addTexture("Textures/HUD/MurdochInside.png","cover");
	TextureManager::Instance()->addTexture("Textures/HUD/menu.png","menu");
	TextureManager::Instance()->addTexture("Textures/HUD/btn_ng.png","btn_ng");
	TextureManager::Instance()->addTexture("Textures/HUD/btn_ng_d.png","btn_ng_d");
	TextureManager::Instance()->addTexture("Textures/HUD/btn_eg.png","btn_eg");
	TextureManager::Instance()->addTexture("Textures/HUD/btn_eg_d.png","btn_eg_d");
	TextureManager::Instance()->addTexture("Textures/HUD/btn_rsm.png","btn_rsm");
	TextureManager::Instance()->addTexture("Textures/HUD/btn_rsm_d.png","btn_rsm_d");
	TextureManager::Instance()->addTexture("Textures/HUD/BeerTek.png","BeerTek");
	TextureManager::Instance()->addTexture("Textures/HUD/TavernSimLogo.png","TavernSimLogo");

	int window_W = glutGet(GLUT_WINDOW_WIDTH);
	int window_H = glutGet(GLUT_WINDOW_HEIGHT);
	SetBufferRef();
	MenuContainer* bg = newContainer("bg",0,0,1300,1000,"cover");
	MenuButton* thx = newButton("thx",350, 25, 512, 768,"thanks","thanks");
	MenuContainer* cont1 = newContainer("cont1",745,260,310,200,"menu");
	MenuContainer* cont2 = newContainer("cont2",345,530,512,256,"TavernSimLogo");
	MenuButton* btn1 = newButton("btn1",750,375,300,50,"btn_ng","btn_ng_d");
	MenuButton* btn2 = newButton("btn2",750,300,300,50,"btn_eg","btn_eg_d");
	btn1->addListener(resume);
	btn2->addListener(showexit);
	thx->addListener(exit);
	cont1->addChild(btn1);
	cont1->addChild(btn2);
	cont1->addChild(cont2);
	bg->addChild(cont1);
	MenuDisplay("bg");
}

MenuSystem::~MenuSystem()
{
	map<string,MenuComponent*>::iterator i;
	for(i=components.begin();i!=components.end();i++)
	{
		delete i->second;
	}
	components.clear();
}

void MenuSystem::SetBufferRef()
{
	((OpenGL *)RenderingEngine::Instance()->GetRenderHandle())->AddRefToBuffer(m_objectID, this);
}

void MenuSystem::Destory()
{
	((OpenGL *)RenderingEngine::Instance()->GetRenderHandle())->EraseRefFromBuffer(m_objectID);
}