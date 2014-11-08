#pragma once

#include "..\glm\glm.hpp"
#include "collide_fine.h"


/**
	*@brief BSphere
	*
	* Inheritance from CollisionSphere
	* 
*/
class BSphere : public cyclone::CollisionSphere
{
public:
	BSphere(float radius, glm::vec3 position,float mass, cyclone::collisionType type);
	~BSphere(void);
	cyclone::Vector3 position;
	void Draw();
};

