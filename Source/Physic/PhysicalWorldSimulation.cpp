#include "PhysicalWorldSimulation.h"
#include <iostream>


PhysicalWorldSimulation * PhysicalWorldSimulation::Instance()
{
	static PhysicalWorldSimulation ins;
	return &ins;
}

void PhysicalWorldSimulation::init()
{
	cData.contactArray = contacts;
}


void PhysicalWorldSimulation::AddBSphere(float radius, glm::vec3 pos, float mass,cyclone::collisionType type)
{
	BSphere * temp = new BSphere(radius, pos, mass, type);
	WorldContainer.push_back(temp);
}


void PhysicalWorldSimulation::AddBBox(float half_x, float half_y, float half_z, glm::vec3 position, float mass, cyclone::collisionType type, float xRot, float yRot, float zRot)
{
	Bbox * temp = new Bbox(half_x, half_y,half_z, position,mass,type, xRot, yRot, zRot);
    WorldContainer.push_back(temp);
}


void PhysicalWorldSimulation::AddBBox(Bbox * bbox)
{
	WorldContainer.push_back(bbox);
}




void PhysicalWorldSimulation::Update(cyclone::real dt)
{
	if(pauseSimulation)
	{
		return;
	}
	//update the objects
	updateObject(dt);
	generateContacts();
	resolver.resolveContacts(cData.contactArray, cData.contactCount,dt);

}

void PhysicalWorldSimulation::updateObject(cyclone::real dt)
{
	for(int i = 0; i < WorldContainer.size(); i++)
	{
		((cyclone::CollisionPrimitive *)(WorldContainer[i]))->body->integrate(dt);
		WorldContainer[i]->calculateInternals();
	}
}

void PhysicalWorldSimulation::generateContacts()
{
	hit = false;
	//create the ground plane Data

	cyclone::CollisionPlane plane;
	plane.direction = cyclone::Vector3(0,1,0);
	plane.offset = -45.0;

	//Set up the collision data structure
	cData.reset(MaxContacts);
	cData.friction = (cyclone::real)0.9;
	cData.restitution = (cyclone::real)0.2;
	cData.tolerance = (cyclone::real)0.1;

	cyclone::Matrix4 transform, otherTransform;
	cyclone::Vector3 position, otherPosition;

	for(int i = 0; i < WorldContainer.size(); i++)
	{
		
	
		
		if( dynamic_cast<cyclone::CollisionSphere *>(WorldContainer[i]) != nullptr)
		{

			  cyclone::CollisionDetector::sphereAndHalfSpace( *(cyclone::CollisionSphere *)(WorldContainer[i]) , plane, &cData);

			  if(!cData.hasMoreContacts()) return;
			 for(int j = i + 1; j < WorldContainer.size(); j++)
			 {

			      if(!cData.hasMoreContacts()) return;
				  if( dynamic_cast<cyclone::CollisionSphere *>(WorldContainer[j]) != nullptr)
				  {
					  cyclone::CollisionDetector::sphereAndSphere(*(cyclone::CollisionSphere *)(WorldContainer[i]),
						                                          *(cyclone::CollisionSphere *)(WorldContainer[j]),
																   &cData);
					 
				  }
				  else if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[j]) != nullptr)
				  {
					   cyclone::CollisionDetector::boxAndSphere( *(cyclone::CollisionBox *)(WorldContainer[j]),
						                                         *(cyclone::CollisionSphere *)(WorldContainer[i]),
																 &cData);
				  }

			 }
		}
		else if( dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != nullptr)
		{
			if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type != cyclone::collisionType::STATIC )
			{
				cyclone::CollisionDetector::boxAndHalfSpace( *(cyclone::CollisionBox *)(WorldContainer[i]) , plane, &cData);
			}


			 if(!cData.hasMoreContacts()) return;
			 for(int j = i + 1; j < WorldContainer.size(); j++)
			 {

				  if(!cData.hasMoreContacts()) return;
				  if( dynamic_cast<cyclone::CollisionSphere *>(WorldContainer[j]) != nullptr)
				  {
					   cyclone::CollisionDetector::boxAndSphere(*(cyclone::CollisionBox *)(WorldContainer[i]),
						                                        *(cyclone::CollisionSphere *)(WorldContainer[j]),
																 &cData);
				  }

				  /*
				   (dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type != cyclone::collisionType::STATIC||
				          dynamic_cast<cyclone::CollisionBox *>(WorldContainer[j])->type != cyclone::collisionType::STATIC))
						  */
				  else if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[j]) != nullptr &&
					      (dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type != cyclone::collisionType::STATIC ||
						   dynamic_cast<cyclone::CollisionBox *>(WorldContainer[j])->type != cyclone::collisionType::STATIC
					  )) 
				  {
					   cyclone::CollisionDetector::boxAndBox(*(cyclone::CollisionBox *)(WorldContainer[i]),
						                                     *(cyclone::CollisionBox *)(WorldContainer[j]),
															  &cData);
				  }
			 }
		}
	}
}

bool PhysicalWorldSimulation::CollisionWithWall(cyclone::CollisionPrimitive * body)
{
	if(WorldContainer.size() < 2)
		return 0;


	for(int i =0; i < WorldContainer.size(); i++)
	{
		if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != nullptr   &&  
		   dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type == cyclone::collisionType::STATIC &&
		   dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != body)
		{
			if( cyclone::IntersectionTests::boxAndBox(*(cyclone::CollisionBox *)(WorldContainer[i]),*(cyclone::CollisionBox *)body))
			{
				return 1;
			}
		}
	}
	return 0;
}


bool PhysicalWorldSimulation::checkWorldPointForStaticBox(const cyclone::Vector3 point)
{
	if(WorldContainer.size() < 2)
		return 0;
	Bbox* temp = new Bbox(1, 1, 1, glm::vec3(point.x, point.y, point.z), 1,cyclone::collisionType::NORMAL,0.0001,0.00001,0.0001);

	for(int i =0; i < WorldContainer.size(); i++)
	{
		if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != nullptr   &&  
		   dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type == cyclone::collisionType::STATIC)
		{
			if( cyclone::IntersectionTests::boxAndBox(*(cyclone::CollisionBox *)(WorldContainer[i]),*(cyclone::CollisionBox *)temp))
			{
				temp = nullptr;
				return 1;
			}
		}
	}
	return 0;
}

bool PhysicalWorldSimulation::checkWorldPointForStaticBox(float x, float y, float z)
{
	bool collision = false;

	cyclone::Vector3 point(x, y, z);

	if(WorldContainer.size() < 2)
	{	
		std::cout << "worldcontainer size is less than 2." << std::endl;
		return(false);
	}

	glm::vec3 min = glm::vec3(10000000,10000000,10000000);
	glm::vec3 max = glm::vec3(0,0,0);
	
	Bbox* temp = new Bbox((max.x - min.x)/2,  
				          (max.y - min.y)/2,  
						  (max.z - min.z)/2, glm::vec3(point.x, point.y, point.z), 1,
						   cyclone::collisionType::NORMAL, 0.0001, 0.00001, 0.0001);

	for(int i = 0; i < WorldContainer.size(); i++)
	{
		if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != nullptr   &&  
		   dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type == cyclone::collisionType::STATIC)
		{
			if( cyclone::IntersectionTests::boxAndBox(*(cyclone::CollisionBox *)(WorldContainer[i]),*(cyclone::CollisionBox *)temp))
			{
				temp = nullptr;
				return(true);
			}
		}
	}

	return(collision);
}

cyclone::CollisionPrimitive * PhysicalWorldSimulation::IntersectWithRay(cyclone::CollisionPrimitive * body, cyclone::Ray & ray)
{
	if(	 WorldContainer.size() < 2)
		return nullptr;

	for(int i =0; i < WorldContainer.size(); i++)
	{


			if(dynamic_cast<cyclone::CollisionSphere *>(WorldContainer[i]) != nullptr   &&  
			   dynamic_cast<cyclone::CollisionSphere *>(WorldContainer[i])->type == cyclone::collisionType::NORMAL &&
			   dynamic_cast<cyclone::CollisionSphere *>(WorldContainer[i]) != body)
			{
			
				if(cyclone::IntersectionTests::ShpereAndRay(ray,*(cyclone::CollisionBox *)body,*(cyclone::CollisionSphere *)(WorldContainer[i])))
				{

					    double distance = std::pow( ( ((cyclone::CollisionSphere *)(WorldContainer[i]))->body->getPosition().x 
						                - body->body->getPosition().x) ,2)
                                      +
									   std::pow( ( ((cyclone::CollisionSphere *)(WorldContainer[i]))->body->getPosition().z 
						                - body->body->getPosition().z) ,2);
                         

						 std::cout <<"Item " << ((cyclone::CollisionSphere *)(WorldContainer[i]))->body->getPosition().x << " : " <<  ((cyclone::CollisionSphere *)(WorldContainer[i]))->body->getPosition().z << std::endl;
						 std::cout <<"Character " <<  body->body->getPosition().x << " : " << body->body->getPosition().z  << std::endl;
					     distance = sqrt(distance);
						 std::cout << "distance " << distance << std::endl; 
						 if(distance <= 100)
						 {
							  return (cyclone::CollisionPrimitive *)(WorldContainer[i]);
						 }
						
						 return nullptr;
				}

			}
			else if(dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != nullptr   &&  
				    dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i])->type == cyclone::collisionType::NORMAL &&
					dynamic_cast<cyclone::CollisionBox *>(WorldContainer[i]) != body)
			{

				if(cyclone::IntersectionTests::boxAndRay(ray,*(cyclone::CollisionBox *)body,*(cyclone::CollisionBox *)(WorldContainer[i])))
				{

					    double distance = std::pow( ( ((cyclone::CollisionBox *)(WorldContainer[i]))->body->getPosition().x 
						                - body->body->getPosition().x) ,2)
                                      +
									   std::pow( ( ((cyclone::CollisionBox *)(WorldContainer[i]))->body->getPosition().z 
						                - body->body->getPosition().z) ,2);
                              
					     std::cout <<"Item " << ((cyclone::CollisionBox *)(WorldContainer[i]))->body->getPosition().x << " : " <<  ((cyclone::CollisionBox *)(WorldContainer[i]))->body->getPosition().z << std::endl;
						 std::cout <<"Character " <<  body->body->getPosition().x << " : " <<  body->body->getPosition().z  << std::endl;
					     distance = sqrt(distance);
					     std::cout << "distance " << distance << std::endl; 
						 if(distance <= 100)
						 {
							 return (cyclone::CollisionPrimitive *)(WorldContainer[i]);
						 }

						 return nullptr;
				}

			}

	}
	return nullptr;
}

void PhysicalWorldSimulation::ThrowObj(cyclone::CollisionPrimitive * body,cyclone::Vector3 vel)
{
	body->body->setVelocity(vel);
}



void PhysicalWorldSimulation::Display()
{
	for(int i =0; i < WorldContainer.size(); i++)
	{
		((cyclone::CollisionPrimitive *)WorldContainer[i])->Draw();
	}
}