#include "ControlSystem.h"
#include "InputEngine.h"
#include "RenderingEngine.h"
#include "World.h"
#include "TextureManager.h"
#include "OpenGL.h"
#include "MenuSystem.h"
#include "ResourceManager.h"
#include "Physic\PhysicEngine.h"



ControlSystem* ControlSystem::Instance()
{
	static ControlSystem Instance;
	return &Instance;
}

void ControlSystem::init()
{
	input =  InputEngine::Instance();
	hud.SetBufferRef();

	status = GAME_STOP;
}

void ControlSystem::setStatus(GameStatus gs)
{
	status = gs;
}

GameStatus ControlSystem::getStatus()
{
	return status;
}
//user of program puts everything in here
void ControlSystem::Update(double deltaTime)
{
	if(!hud.getSplash())
	{
		if(status != GAME_EXIT)
		{
			if(input->getKeyDown(KeyCode::Esc))
			{
				//hud.switchManual();
				MenuSystem::switchMenu();
				InputEngine::Instance()->switchFixedMouse();
				status = status == GAME_RUN ? GAME_STOP : GAME_RUN;
			}
		}
		if(status == GAME_RUN)
		{
			if(input->getKeyDown(KeyCode::Esc))
			{
				//input->switchFixedMouse();
				//
				hud.setExit(true);
			}

			if(input->getMouseDown(MouseCode::LeftClick) && hud.getExit())
			{
				status = GAME_STOP;
				MenuSystem::Instance()->MenuDisplay("cont2");
				MenuSystem::openMenu();
				input->switchFixedMouse();
				//exit(0);
			}

			if(input->getKeyUp(KeyCode::B))
			{
				PhysicEngine::Instance()->switchRenderMode();
			}
		}
		else
		{
			if(input->getMouseDown(MouseCode::LeftClick))
			{
				MenuSystem::Instance()->checkPressedButton(input->getMousePoint());
			}
			if(input->getMouseUp(MouseCode::LeftClick))
			{
				MenuSystem::Instance()->unpressButton(input->getMousePoint());
			}
		}
	}
	else
	{
		if(input->getMouseDown(MouseCode::LeftClick))
			{
				hud.turnOffSplash();
			}
	}
}
