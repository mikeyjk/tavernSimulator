#ifndef AFFORDANCE_SYSTEM_H
#define AFFORDANCE_SYSTEM_H

///Class Affordance System
/// Has Access to the world class so that it can query all of the objects in the scene around a point for an entity to know what is nearby

#include <vector>
//#include "World.h"
#include "Global_Structs.h"

struct Vec3
{
	float x;
	float y;
	float z;
};



struct Affordance{
	enTag tag;
	float range;//0.0-0.55-1.0 range(100%)
	//maybe entity
};




using namespace std;

class AffordanceSystem
{
public:
	static AffordanceSystem* Instance();
	AffordanceSystem(){};
	~AffordanceSystem(){};

	/// this might need to be changed.. dependant on how It is returned from entities.
	/// two possibilities affordance has a pointer to an entity, or return a pointer to the entity
	/// Would like to have it affordance with an entity, but might be memory waste.
	vector<Affordance> QueryWorld(Vec3 pos, float radius);

private:
	//need a pointer to the world class to be enabled to view everything
	//World* world;
};

#endif