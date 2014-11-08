#include "HUD.h"
#include "RenderingEngine.h"
#include "OpenGL.h"
#include "IdGenerator.h"
#include "World.h"
#include "ControlSystem.h"
#include "ResourceManager.h"

HUD::HUD()
{
	RederingHandle = RenderingEngine::Instance();
	IdGen = IdGenerator::Instance();
	m_objectID = IdGen->GetID();
	isManual = false;
	Ex = false;
	splash = true;
}

HUD::~HUD()
{
	Destory();
}

void HUD::Destory(void)
{
	((OpenGL *)RederingHandle->GetRenderHandle())->EraseRefFromBuffer(m_objectID);
}

void HUD::Draw()
{
	OpenGL* openGL = ((OpenGL *)RederingHandle->GetRenderHandle());

	if(Ex == true)
	{
		openGL->RenderOverlay(250, 250, 500, 500, "thanks");
	}
	else
	{
		if(overlayData)
		{
			int x1 = 55;
			//row 1 75
			std::ostringstream ssStr;
			ssStr.precision(4);
			ssStr << overlayData->Phys.Strength << "/" << overlayThreshold->Phys.Strength;
			std::string strength(ssStr.str());
			openGL->renderString(x1, 160, strength, 2);

			std::ostringstream ssAg;
			ssAg << overlayData->Phys.Agile << "/" << overlayThreshold->Phys.Agile;
			std::string Agile(ssAg.str());
			openGL->renderString(x1, 143, Agile, 2);

			std::ostringstream ssStom;
			ssStom << overlayData->Phys.Stomach << "/" << overlayThreshold->Phys.Stomach;
			std::string Stomach(ssStom.str());
			openGL->renderString(x1, 126, Stomach, 2);

			std::ostringstream ssSight;
			ssSight << overlayData->Phys.Sight << "/" << overlayThreshold->Phys.Sight;
			std::string Sight(ssSight.str());
			openGL->renderString(x1, 109, Sight, 2);

			std::ostringstream ssHealth;
			ssHealth << overlayData->Phys.Health << "/" << overlayThreshold->Phys.Health;
			std::string health(ssHealth.str());
			openGL->renderString(x1, 92, health, 2);

			int x2 = 160;
			//row 2 175
			std::ostringstream ss21;
			ss21 << overlayData->Vit.Hunger << "/" << overlayThreshold->Vit.Hunger;
			std::string hunger(ss21.str());
			openGL->renderString(x2, 160, hunger, 2);

			std::ostringstream ss22;
			ss22 << overlayData->Vit.Thirst << "/" << overlayThreshold->Vit.Thirst;
			std::string Thirst(ss22.str());
			openGL->renderString(x2, 143, Thirst, 2);

			std::ostringstream ss23;
			ss23 << overlayData->Vit.Bladder << "/" << overlayThreshold->Vit.Bladder;
			std::string Bladder(ss23.str());
			openGL->renderString(x2, 126, Bladder, 2);

			std::ostringstream ss24;
			ss24 << overlayData->Vit.Tiredness << "/" << overlayThreshold->Vit.Tiredness;
			std::string Tiredness(ss24.str());
			openGL->renderString(x2, 109, Tiredness, 2);

			std::ostringstream ss25;
			ss25 << overlayData->Vit.Toxication << "/" << overlayThreshold->Vit.Toxication;
			std::string Toxication(ss25.str());
			openGL->renderString(x2, 92, Toxication, 2);


			//row 3 275
			int x3 = 262;
			std::ostringstream ss31;
			ss31 << overlayData->Ment.Memory << "/" << overlayThreshold->Ment.Memory;
			std::string Memory(ss31.str());
			openGL->renderString(x3, 160, Memory, 2);

			std::ostringstream ss32;
			ss32 << overlayData->Ment.Talk << "/" << overlayThreshold->Ment.Talk;
			std::string Talk(ss32.str());
			openGL->renderString(x3, 143, Talk, 2);

			std::ostringstream ss33;
			ss33 << overlayData->Ment.Curiosity << "/" << overlayThreshold->Ment.Curiosity;
			std::string Curiosity(ss33.str());
			openGL->renderString(x3, 126, Curiosity, 2);

			std::ostringstream ss34;
			ss34 << overlayData->Ment.Boredom << "/" << overlayThreshold->Ment.Boredom;
			std::string Boredom(ss34.str());
			openGL->renderString(x3, 109, Boredom, 2);

			std::ostringstream ss35;
			ss35 << overlayData->Ment.Fear << "/" << overlayThreshold->Ment.Fear;
			std::string Fear(ss35.str());
			openGL->renderString(x3, 92, Fear, 2);

			std::ostringstream ssTrait;
			for(auto t : TraitData)
			{
				ssTrait << t.name << ", ";
			}
			std::string traitStr(ssTrait.str());

			openGL->renderString(x1, 61, traitStr, 2);

			std::ostringstream ssAfford1;

			for(auto a : m_affordances)
			{
				ssAfford1 << Affordance::tagToString(a.getTag()) << ", ";
			}
			std::string affordStr1(ssAfford1.str());

			openGL->renderString(x1+33, 48, affordStr1, 2);

			std::ostringstream ssEm;
			ssEm << enEmotionToString(*dispEmotion);
			std::string Emotion(ssEm.str());
			openGL->renderString(x1+10, 75, Emotion, 2);

			//Michaels Stuff
			std::ostringstream npcido;
			npcido << npcid;
			std::string npcids(npcido.str());

			openGL->renderString(500, 170, "NPC# " + npcids, 3);
			openGL->renderString(500, 140, "	State: " + stateName, 3);

			std::ostringstream ssNeeds;
			for(auto need : needs)
			{
				ssNeeds << need + ", ";
			}
			std::string needstr(ssNeeds.str());
			openGL->renderString(500, 110, "	Needs: " + needstr, 3);

			std::ostringstream ssAfford;
			for(auto aff : afforded)
			{
				//Tag temp = static_cast<Tag>(aff);
				ssAfford << to_string(aff) + ", ";
			}
			std::string affordStr(ssAfford.str());
			openGL->renderString(500, 90, "	Afforded by local entity: " + affordStr, 3);


			openGL->RenderOverlay(10,40,300, 150, "AIPanel");
			openGL->RenderOverlay(470,80,250, 120, "menu");
		}
	}
}

void HUD::giveHudNPCData(int npcid, std::string stateName, std::vector<std::string> needs, std::vector<int> afford)
{
	this->npcid = npcid;
	this->stateName = stateName;
	this->needs = needs;
	this->afforded = afford;
}

void HUD::DrawSplash()
{
	OpenGL* openGL = ((OpenGL *)RederingHandle->GetRenderHandle());
	openGL->renderString(512, 125, "Click to continue", 3);
	openGL->RenderOverlay(100,100,1024, 512, "BeerTek");
}

void HUD::SetBufferRef()
{
	((OpenGL *)RederingHandle->GetRenderHandle())->AddRefToBuffer(m_objectID, this);
}

void HUD::setManual(bool m)
{
	isManual = m;
}

bool HUD::getManual()
{
	return isManual;
}

void HUD::switchManual()
{
	isManual = !isManual;
}


string HUD::enEmotionToString(enEmotion em)
{
	switch(em)
	{
	case Esctatic:
		return "Esctatic";
		break;
		
	case Joy:
		return "Joy";
		break;
		
	case Happy:
		return "Happy";
		break;
		
	case Fine:
		return "Fine";
		break;
		
	case Complacent:
		return "Complacent";
		break;
		
	case Sad:
		return "Sad";
		break;
		
	case Desolate:
		return "Desolate";
		break;
		
	case Angry:
		return "Angry";
		break;
		
	case Rage:
		return "Rage";
		break;
	default:
		break;
	}


}

