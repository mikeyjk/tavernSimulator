#include "WorldFactory.h"
#include "RenderingEngine.h"

WorldFactory::WorldFactory(void)
{

	rederingEngine = RenderingEngine::Instance();
}

WorldFactory::~WorldFactory(void)
{
}

/**
 * Create an object in the game world.
 * Objects are of 3 types.
 * Character, Geometry and SkyBox.
 */
GameObject* WorldFactory::CreateObject(string name, Vec3 pos, float rotX, float rotY, string model, string texture, bool bound, float transparency, float weight, std::vector<Affordance> affordances, std::vector<std::string> traits)
{
	if(name == "Character")
	{
		return new Character(rederingEngine, pos, rotX, rotY, model, texture, bound, affordances);
	}
	else if(name == "Geometry")
	{
		return new Geometry(rederingEngine, pos, rotX, rotY, model, texture, bound, transparency, affordances, weight);
	}
	else if(name == "NPC")
	{
		return new NPC(rederingEngine, pos, rotX, rotY, model, texture, bound, affordances, traits, weight);
	}
	else if(name == "SkyBox")
	{
		return new SkyBox(rederingEngine, pos, texture);
	}
	else
	{
		std::cout << "Error, unexpected input: " << name << std::endl;
		return(nullptr);
	}
}


