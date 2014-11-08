#include "NPC.h"

NPC::NPC(RenderingEngine* Ref, Vec3 pos, float rotX, float rotY, 
		 string model, string texture, bool bound, std::vector<Affordance> affordances, std::vector<std::string> traits,float weight)
		 :GameObject(Ref, pos, rotX, rotY, model, texture, bound, trans, weight)
{
	this->RederingHandle = Ref;
	// type = gameObjectType::character;

	m_ps =  PhysicalWorldSimulation::Instance();

	m_stateMachine = new StateMachine<NPC>(this); 
	m_stateMachine->SetCurrentState(Wander::Instance());

	// Create the BoundingBox for Camera
	//body = new Bbox(20,35,20, glm::vec3(pos.X, pos.Y, pos.Z),100.0, cyclone::collisionType::STATIC,0,0,0);
	//PhysicalWorldSimulation::Instance()->WorldContainer.push_back(body);
	canPick  = true;
	pickedObj = nullptr;
	SetBufferRef();

	myBrain.initPersonality("null","null","null","null");

	for(auto i: traits)
	{
		std::string tr = i;
		tr.replace(tr.begin(), tr.begin()+7, "");
		myBrain.addTrait(tr);
	}

	setAffordances(affordances);
	type = npc;
}

NPC::~NPC()
{
	this->Destory();
}

void NPC::Destory(void)
{
	((OpenGL *)RederingHandle->GetRenderHandle())->EraseRefFromBuffer(m_objectID);
}

void NPC::SetBufferRef()
{
	((OpenGL *)RederingHandle->GetRenderHandle())->AddRefToBuffer(m_objectID, this);
}

std::string NPC::getState()
{
	return(m_stateMachine->GetNameOfCurrentState());
}

void NPC::Update(double deltaTime)
{
	myBrain.update(deltaTime);
	giveHudMoreData();

	// if we have needs
	if(myBrain.getNeeds().size() > 0)
	{
		// check to see if we can find things afforded to us
		myBrain.giveAffordancesThatMeetNeeds(getLocalAffordances());
		if(!targetObject || m_stateMachine->GetNameOfCurrentState() == "Wander")
		{
			Tag newState;
			targetObject = myBrain.calculateTarget(newState);
			m_stateMachine->ChangeState(Affordance::tagToState(newState));
		}
	}

   m_stateMachine->Update();
}

// check all NPC's, if they have a need
// then check all Game Object's within a certain radius
// to see if they afford the NPC's need
// if it does then we store the game object 
vector<GameObject*> NPC::getLocalAffordances()
{
	std::vector<GameObject*> afforded;

	// check all of NPC's needs
	for(Tag need : myBrain.getNeeds())
	{
		// for every collidable object (we have a local copy)
		for(auto gameObj : m_getAllCollidable)
		{	
			// if there is a valid GameObject* ptr
			if(gameObj.second != nullptr)
			{
				// don't check against self
				if(gameObj.second != this)
				{
					// check if within range of NPC
					Vec3 target = gameObj.second->getPos();
					Vec3 pos = getPos();

					float targetDistance = (target - pos).length();

					if(targetDistance < myBrain.getSight() * 3)
					{
						// iterate through this GameObjects's affordances
						for(Affordance& affordance : gameObj.second->getAffordances())
						{
							// if affordance = need
							if(need == affordance.getTag())
							{
								// a need of this NPC is afforded to it
								// return this information
								afforded.push_back(gameObj.second);
							}
						}
					}
				}
			}
		}
	}
	
	return(afforded);
}

void NPC::Draw()
{
	if(isBounding)
	{
		m_position.X = Bounding->body->getPosition().x;
		m_position.Y = Bounding->body->getPosition().y;
		m_position.Z = Bounding->body->getPosition().z;

		float q0 = Bounding->body->getOrientation().r;
		float q1 = Bounding->body->getOrientation().i;
		float q2 = Bounding->body->getOrientation().j;
		float q3 = Bounding->body->getOrientation().k;
		
		m_rotation.X = std::atan2( 2 * (q0 * q1 + q2 * q3),  1 - 2 * ( q1 * q1 + q2 * q2)); 
		m_rotation.Y = std::asin( 2 * (q0 * q2 - q3 * q1));
		m_rotation.Z = std::atan2( 2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));

		float temp = 180.0 / 3.1415926;
		m_rotation.X *= temp;
		m_rotation.Y *= temp;
		m_rotation.Z *= temp;

		//std::cout << " X:" << m_rotation.X << "  Y:" << m_rotation.Y << " Z:" << m_rotation.Z << std::endl; 
		
		glPushMatrix();
		GLfloat mat[16];
		Bounding->body->getGLTransform(mat);
		((Bbox*)Bounding->body)->halfSize;
		glMultMatrixf(mat);
		RederingHandle->DrawModel(model, texture, trans, Vec3(0,0,0), Vec3(0,0,0), Vec3(1, 1, 1));
		glPopMatrix();
	}
	else
	{   
		glPushMatrix();
		GLfloat mat[16];
		Bounding->body->getGLTransform(mat);
		glMultMatrixf(mat);
		RederingHandle->DrawModel(model, texture, trans, Vec3(0,0,0), Vec3(0,0,0), Vec3(1, 1, 1));
		glPopMatrix();
	}
}

/**
void NPC::changeState(State* newState)
{
	// check current state and new state are valid

	// delete current state
	m_currentState->exit(m_currentState);

	// swap to new state
	m_currentState = newState;

	// enter into new state
	m_currentState->enter(m_currentState);
}*/
