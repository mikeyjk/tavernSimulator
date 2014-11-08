#pragma once
#include "cyclone.h"
#include "..\glm\glm.hpp"
#include "BSphere.h"
#include "Bbox.h"
#include <vector>
class PhysicalWorldSimulation
{
public:
	

	
    /**
	*@brief Singleton
	*
	* Create a singleton
	* 
    */
	static PhysicalWorldSimulation * Instance();

	/**
	*@brief init
	*
	* Initialize the world
	* 
    */
	void init();


	/**
	*@brief Ray cast
	*
	* Cast a ray from mouse
	* 
    */
	void MouseRayCast();

	/**
	*@brief Add Bounding sphere
	*
	* Add a Bounding sphere into world
	* 
    */
	void AddBSphere(float radius, glm::vec3 pos, float mass,cyclone::collisionType type);

	/**
	*@brief Add Bounding box
	*
	* Add a Bounding sphere into box
	* 
    */
	void AddBBox(float half_x, float half_y, float half_z, glm::vec3 position, float mass,cyclone::collisionType type, float xRot, float yRot, float zRot);

	void AddBBox(Bbox * bbox);

	


	const static unsigned MaxContacts = 1000;
	cyclone::Contact contacts[MaxContacts];
	cyclone::CollisionData cData;
	cyclone::ContactResolver resolver;
	bool pauseSimulation;
	float frameSpeed;

    /**
	*@brief Generate contacts
	*
	* Generates contacts point between objects
	* 
    */
	void generateContacts();

   /**
	*@brief Update the condition of obj
	*
	* Update obj
	* 
    */
	void updateObject(cyclone::real duration);

	 /**
	*@brief Update the world
	*
	* Update world
	* 
    */
	void Update(cyclone::real dt);

	/**
	*@brief display
	*
	* Draw obj
	* 
    */
	void Display();


	/**
	*@brief collision
	*
	* Check the collision between camera and wall
	* 
    */
	bool CollisionWithWall(cyclone::CollisionPrimitive * body);
	
	bool checkWorldPointForStaticBox(const cyclone::Vector3 point);

	bool checkWorldPointForStaticBox(float x, float y, float z);

   /**
	*@brief Intersection
	*
	* Check the intersection between obj and Ray
	* 
    */
	cyclone::CollisionPrimitive * IntersectWithRay(cyclone::CollisionPrimitive * body, cyclone::Ray & ray);
	/**
	*@brief ThrowObj
	*
	* Throw the obj 
	* 
    */
	void ThrowObj(cyclone::CollisionPrimitive * body , cyclone::Vector3 vel);
	std::vector<cyclone::Collision *> WorldContainer;
	bool hit;

private:

	PhysicalWorldSimulation(void){}
	~PhysicalWorldSimulation(void){}
};

