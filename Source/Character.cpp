#include "Character.h"
#include "NPC.h"

Character::Character(RenderingEngine* Ref, Vec3 pos, float rotX, float rotY, string model, string texture, bool bound, std::vector<Affordance> affordances)
					:GameObject(Ref, pos, rotX, rotY, model, texture, bound, trans, 100)
{
	input = InputEngine::Instance();
	Camera * cam = RederingHandle->GetCamera();
	this->RederingHandle = Ref;
	cam->SetPosition(pos);
	type = gameObjectType::character;

	//Create the BoundingBox for Camera
	body = new Bbox(10,25,10, glm::vec3(pos.X, pos.Y, pos.Z),100.0, cyclone::collisionType::NORMAL,0,0,0);
	PhysicalWorldSimulation::Instance()->WorldContainer.push_back(body);

	canPick  = true;
	pickedObj = nullptr;
	SetBufferRef();

	setAffordances(affordances);
	control = ControlSystem::Instance();
}

Character::~Character(void)
{
	input = nullptr;
	this->Destory();
}

void Character::Destory(void)
{
	((OpenGL *)RederingHandle->GetRenderHandle())->EraseRefFromBuffer(m_objectID);
}

void Character::SetBufferRef()
{
	((OpenGL *)RederingHandle->GetRenderHandle())->AddRefToBuffer(m_objectID, this);
}

void Character::Update(double deltaTime)
{

	Camera * cam = RederingHandle->GetCamera();
	float Speed =  cam->GetSpeed();
	
	Vec2 mouse = input->getAlphaMousePoint();
	float x = mouse.x;
	float y = mouse.y;
	
	if(x != 0)
	{
	  cam->RotateYaw(x);
	}
	if(y != 0)
	{
	  cam->RotatePitch(y);
	}
	
	Vec3 velocity;
	Vec3 subVelLeft;
	Vec3 subVelRight;
	Vec3 subVelForward;
	Vec3 subVelBack;

	if(input->getKey(KeyCode::A))
	{
		Vec3 temp(cam->GetSide().getX(), 0, cam->GetSide().getZ());
		Vec3 NewPosition( m_position.getX() + temp.getX() * Speed,
			              m_position.getY(),
						  m_position.getZ() + temp.getZ() * Speed);
		subVelLeft = NewPosition - m_position;


	}
	
	if(input->getKey(KeyCode::D))
	{
		Vec3 temp(cam->GetSide().getX(), 0, cam->GetSide().getZ());
		Vec3 NewPosition( m_position.getX() - temp.getX() * Speed,
			              m_position.getY(),
						  m_position.getZ() - temp.getZ() * Speed);
		subVelRight = NewPosition - m_position;

	}
	
	if(input->getKey(KeyCode::W))
	{
		Vec3 temp(cam->GetDirection().getX(), 0, cam->GetDirection().getZ());
		Vec3 NewPosition( m_position.getX() + temp.getX() * Speed,
			              m_position.getY(),
						  m_position.getZ() + temp.getZ() * Speed);
		
		subVelForward = NewPosition - m_position;

		
	}

	if(input->getKey(KeyCode::S))
	{
		Vec3 temp(cam->GetDirection().getX(), 0, cam->GetDirection().getZ());
		Vec3 NewPosition( m_position.getX() - temp.getX() * Speed,
			              m_position.getY(),
						  m_position.getZ() - temp.getZ() * Speed);
		
		subVelBack = NewPosition - m_position;

	

	}
	if(input->getKeyUp(KeyCode::A))
	{
		subVelLeft = Vec3(0,0,0);
	}

	if(input->getKeyUp(KeyCode::D))
	{
		subVelRight = Vec3(0,0,0);
	}

	if(input->getKeyUp(KeyCode::W))
	{
		subVelForward = Vec3(0,0,0);
	}

	if(input->getKeyUp(KeyCode::S))
	{
		subVelBack = Vec3(0,0,0);
	}

	if(input->getKeyUp(KeyCode::P))
	{
		std::cout << m_position.getX() << ", " << m_position.getY() << ", " << m_position.getZ() << std::endl;
	}
	velocity = subVelLeft + subVelRight + subVelForward + subVelBack;

	m_position += velocity;
	//Set the camera Position when camera move
	body->body->setOrientation(1,0,0,0);
	body->body->setRotation(0,0,0);
    body->body->setPosition(m_position.X, m_position.Y, m_position.Z);
	body->body->calculateDerivedData();
	body->calculateInternals();
	
	if(PhysicalWorldSimulation::Instance()->CollisionWithWall(this->body))
	{
		m_position -= velocity;
		body->body->setOrientation(1,0,0,0);
		body->body->setRotation(0,0,0);
		body->body->setPosition(m_position.X, m_position.Y, m_position.Z);
		body->body->calculateDerivedData();
		body->calculateInternals();
	}

	RederingHandle->GetCamera()->SetPosition(m_position);

	PickObject();
}

void Character::PickObject()
{
	if(input->getMouseUp(MouseCode::LeftClick) && canPick)
	{
			cyclone::Ray ray;
			//cyclone::Vector3 dir = cyclone::Vector3(input->projectPoint.X,input->projectPoint.Y,input->projectPoint.Z);
			cyclone::Vector3 dir = cyclone::Vector3(Camera::Instance()->GetDirection().X,Camera::Instance()->GetDirection().Y,Camera::Instance()->GetDirection().Z);
			cyclone::Vector3 camPos = cyclone::Vector3(Camera::Instance()->GetPosition().X,Camera::Instance()->GetPosition().Y,Camera::Instance()->GetPosition().Z);

			ray.original = camPos;
			ray.direction = dir;
			ray.direction.normalise();
			ray.length = 1;

			if( (pickedObj = PhysicalWorldSimulation::Instance()->IntersectWithRay(this->body, ray)) != nullptr)
			{
				GameObject* obj = ((GameObject*)((Bbox*)pickedObj)->myGameObject);
				gameObjectType type = obj->getObjecType();
				if( type != npc)
				{
					canPick = false;
				}
				else
				{
					((NPC*)obj)->giveHudData();
					pickedObj = nullptr;
				}
			}
	}
	else if(input->getMouseUp(MouseCode::RightClick) && !canPick)
	{
		pickedObj = nullptr;
		canPick = true;
	}
	else if(input->getMouseUp(MouseCode::LeftClick) && !canPick)
	{
			canPick = true;
	}

	if(!canPick)
	{
		int len = 50;
		pickedObj->body->setAwake();
		pickedObj->body->setPosition( Camera::Instance()->GetPosition().X + Camera::Instance()->GetDirection().X * len,
			                          Camera::Instance()->GetPosition().Y + Camera::Instance()->GetDirection().Y * len,
									  Camera::Instance()->GetPosition().Z + Camera::Instance()->GetDirection().Z * len);
	}
	else
	{  
		if(pickedObj)
		{
			cyclone::Vector3 dir = cyclone::Vector3(Camera::Instance()->GetDirection().X,Camera::Instance()->GetDirection().Y,Camera::Instance()->GetDirection().Z);
			PhysicalWorldSimulation::Instance()->ThrowObj(pickedObj,dir * 100);
			pickedObj = nullptr;
		}
	}
}

void Character::Draw()
{
	//cyclone::Vector3 dir = cyclone::Vector3(input->projectPoint.X,input->projectPoint.Y,input->projectPoint.Z);
	cyclone::Vector3 dir = cyclone::Vector3(Camera::Instance()->GetDirection().X,Camera::Instance()->GetDirection().Y,Camera::Instance()->GetDirection().Z);
	cyclone::Vector3 camPos = cyclone::Vector3(Camera::Instance()->GetPosition().X,Camera::Instance()->GetPosition().Y,Camera::Instance()->GetPosition().Z);
	dir.normalise();
	
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glLineWidth(10);
	
	glBegin(GL_LINES);
	glVertex3f(camPos.x, camPos.y ,camPos.z);
	glVertex3f(camPos.x + dir.x * 50 , camPos.y + dir.y *  50, camPos.z + dir.z *  50);
	glEnd();

	glTranslated(camPos.x + dir.x * 25 , camPos.y + dir.y *  25, camPos.z + dir.z *  25);
	glutSolidSphere(0.2f, 10, 10);
	//glutSolidCube(1);

	glPopMatrix();
}
