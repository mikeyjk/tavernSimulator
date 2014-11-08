#pragma once

#include "GL\freeglut.h"

#include "..\glm\glm.hpp"
#include <vector>
#include "collide_fine.h"



/**
	*@brief BoundingBox
	*
	* Inheritance from CollisionBox
	* 
*/
class Bbox : public cyclone::CollisionBox
{
   public:
	 Bbox(float half_w, float half_h, float half_d, glm::vec3 position, float mass,cyclone::collisionType type,double x, double y, double z);
	 ~Bbox(void);

	 void Update(glm::vec3 Position);
	 //eight corner points
	 //L - LEFT
	 //T - TOP
	 //D - Down
	 //F - Front
	 //B - Back
	 glm::vec3 LTB;
	 glm::vec3 LTF;
	 glm::vec3 LDB;
	 glm::vec3 LDF;

	 glm::vec3 RTB;
	 glm::vec3 RTF;
	 glm::vec3 RDB;
	 glm::vec3 RDF;
	 
	 float width;
	 float height;
	 float Depth;

	 std::vector<glm::vec3> points;
	
	 void * myGameObject;


	void Draw();

};

