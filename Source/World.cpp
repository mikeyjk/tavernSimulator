#include "World.h"

World* World::Instance()
{
	static World staticWorld;
	return &staticWorld;
}

World::World()
{
	m_renderingHandle = RenderingEngine::Instance();
	m_npcShortCut.empty();
	m_mainCharacter = nullptr;
	m_skybox = nullptr;
}

void World::AddSkybox()
{
	if(m_skybox == nullptr)
	{
		std::vector<Affordance> affordances;
		std::vector<std::string> traits;
		m_skybox = static_cast<SkyBox*> (m_worldFactory.CreateObject("SkyBox",Vec3(0,0,0), 
			0, 0, "", "CubeSky", false, 1, 0, affordances, traits));

		m_skybox->SetAttributes(4000);
		m_renderingHandle->AddRefToBuffer(m_skybox->getID(), m_skybox);
	}
}

GameObject* World::AddEntity(string name, Vec3 pos, float rotX, float rotY, 
							 string model, string texture, bool bound, float transparency, float weight,
							 std::vector<Affordance> affordances, std::vector<std::string> traits)
{
	GameObject * temp = m_worldFactory.CreateObject(name, pos, rotX, rotX, model, texture, 
		bound, transparency, weight, affordances, traits);

	temp->setAffordances(affordances);
	
	// Add Pointer reference to OpenGl render buffer
	// Add Pointer reference to World local storage
	m_renderingHandle->AddRefToBuffer(temp->getID(), temp);
	
	// only add a main character if we do not have one assigned
	if(temp->getObjecType() == gameObjectType::character && !m_mainCharacter)
	{
		m_mainCharacter = true; // flag we have a main char
		this->m_collisionEntities.insert(pair<int, GameObject*>(temp->getID(), temp));
	}
	else if(temp->getObjecType() == gameObjectType::npc
		|| temp->getObjecType() == gameObjectType::geometry)
	{
		this->m_collisionEntities.insert(pair<int, GameObject*>(temp->getID(), temp));
		
		// check if NPC
		if(temp->getObjecType() == gameObjectType::npc)
		{
			// store NPC id in shortcut array
			m_npcShortCut.push_back(temp->getID());

			// iterate through NPC's
			// and store the new NPC reference in each of them
			for(int i = 0; i < m_npcShortCut.size(); ++i)
			{
				NPC* npcShort = ((NPC*)GetCollisionEntity(m_npcShortCut[i]));
			
				for(int y = 0; y < m_npcShortCut.size(); ++y)
				{
					auto& itr = npcShort->m_getAllNPC.find(y);

					if(itr == npcShort->m_getAllNPC.end())
					{
						// don't store itself
						if(itr->second != npcShort)
						{
							npcShort->m_getAllNPC.insert(std::pair<int, NPC*>(y, ((NPC*)GetCollisionEntity(m_npcShortCut[y]))));
						}
					}
				}
			}
		}
		else
		{
			// iterate through NPC's
			// and store the new game object reference in each of them
			for(int i = 0; i < m_npcShortCut.size(); ++i)
			{
				// store ref to individual npc
				NPC* npcShort = ((NPC*)GetCollisionEntity(m_npcShortCut[i]));
			
				// iterate through all collidable entities
				for(std::pair<int, GameObject*> collidable : m_collisionEntities)
				{
					// search this individual npc for the colidable entity
					auto& itr = npcShort->m_getAllCollidable.find(collidable.first);

					// if it doesn't exist, insert it
					if(itr == npcShort->m_getAllCollidable.end())
					{
						npcShort->m_getAllCollidable.insert(std::pair<int, GameObject*>(collidable.first, collidable.second));
					}
				}
			}
		}
	}
	else // add non-collidable objects to data structure
	{
		this->m_nonCollisionEntities.insert(pair<int, GameObject*>(temp->getID(), temp));
	}

	temp->setTransparency(transparency);
	
	return temp;
}

// update all world objects
void World::Update(double deltaTime)
{
	// collidable entities
	for(auto entity : m_collisionEntities)
	{
		if(entity.second != nullptr)
		{
			entity.second->Update(deltaTime);
		}
	}

	// non collidable entities
	for(auto entity : m_nonCollisionEntities)
	{
		if(entity.second != nullptr)
		{
			entity.second->Update(deltaTime);
		}
	}
}

GameObject* World::GetCollisionEntity(int ID)
{
	return(this->m_collisionEntities[ID]);
}

GameObject* World::GetNoCollisionEntiy(int ID)
{
	return(this->m_nonCollisionEntities[ID]);
}

Character* World::GetMainCharacter()
{
	if(m_mainCharacter)
	{
		for(auto entity : m_collisionEntities)
		{
			if(entity.second->getObjecType() == gameObjectType::character)
			{
				return(static_cast<Character*>(entity.second));
			}
		}

		return(nullptr);
	}
	else
	{
		return(nullptr);
	}
}

void World::DeleteEntity(int entityId)
{
	// check for removal of main character
	for(auto entity : m_collisionEntities)
	{
		if(entity.second->getObjecType() == gameObjectType::character)
		{
			m_mainCharacter = false;
		}
	}

	m_renderingHandle->EraseRefFromBuffer(entityId);
}
