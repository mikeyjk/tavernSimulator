#include "AIOwnedStates.h"
#include "NPC.h"
#include <string>
#include <stdio.h>
#include "Physic\Bbox.h"
#include "RNG.h"

//---------------------------------------------------
//------------------Flee STATE-----------------------
//---------------------------------------------------

//as Basically every state will involve walking towards a target
void walkTo(NPC* walker, Vec3 TargetPos)
{
		Vec3 target = TargetPos;
		Vec3 pos = walker->getPos();
		Vec3 rotateVec = walker->getRotation();

		const float PI = 3.141592654f;
		float yrotrad = (rotateVec.Y);
		Vec3 d1, d2;

		float speed = ((NPC*)walker)->getSpeed() / 10;

		d1 = (target - pos).normalize();
		d2 = pos + (d1 * speed);
		cyclone::Vector3 cd2 = cyclone::Vector3(d2.X, d2.Y, d2.Z);

		// while the normalised path is occupied by another BB
		if(walker->m_ps->checkWorldPointForStaticBox(cd2))
		{
			std::cout << "collision with wall" << std::endl;
		}
		else
		{
			std::cout << "no collision with wall" << std::endl;
		}

		walker->setPosition(d2);
		walker->setBoundingPos(d2);
}

void walkTo(NPC* walker, GameObject* TargetObject)
{
		Vec3 target = TargetObject->getPos();
		walkTo(walker, target);
}

Vec3 findNewTarget(NPC* walker)
{
		Vec3 pos = walker->getPos();

		float randX = (float)RNG::Instance()->randomIntRange(-100, 100); 
		float x = randX + pos.getX();
		float randZ = (float)RNG::Instance()->randomIntRange(-100, 100); 
		float z = randZ + pos.getZ();
		float height = -40;
		Vec3 newTarget(x, height, z);
		return newTarget;
}

#pragma region
Eat* Eat::Instance()
{
	static Eat instance;

	return &instance;
}

void Eat::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Eat::Execute(NPC* ai)
{
	std::cout <<"EAT!!" << endl;
	walkTo(ai, ai->getTarget());

	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float foodValue = 0;

	if(distance < 50)//some randon number
	{
		vector<Affordance> affordances = ai->getAffordances();
		for(auto aff: affordances)
		{
			if(aff.getTag() == eat)
			{
				foodValue = aff.getValue();
			}
		}
		//give brain values
		ai->getBrain()->ExternalStimuli(eat, foodValue);
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Eat::Exit(NPC* ai)
{
	
}
#pragma endregion eat

#pragma region
Drink* Drink::Instance()
{
	static Drink instance;

	return &instance;
}

void Drink::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Drink::Execute(NPC* ai)
{
	std::cout <<"Drink!!" << endl;
	walkTo(ai, ai->getTarget());

	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float drinkValue = 0;
	float toxicValue = 0;

	if(distance < 50)//some randon number
	{
		vector<Affordance> affordances = ai->getAffordances();
		for(auto aff: affordances)
		{
			if(aff.getTag() == drink)
			{
				drinkValue = aff.getValue();
			}
			if(aff.getTag() == toxic)
			{
				toxicValue = aff.getValue();
			}
		}
		//give brain values
		ai->getBrain()->ExternalStimuli(drink, drinkValue, toxicValue);
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Drink::Exit(NPC* ai)
{
	
}
#pragma endregion drink

#pragma region
Sit* Sit::Instance()
{
	static Sit instance;

	return &instance;
}

void Sit::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Sit::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sitValue = 0;

	if(distance < 30)//some randon number
	{
		vector<Affordance> affordances = ai->getAffordances();
		for(auto aff: affordances)
		{
			
			if(aff.getTag() == sit)
			{
				sitValue = aff.getValue();
			}
		}
		//give brain values
		ai->getBrain()->ExternalStimuli(sit, sitValue);
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Sit::Exit(NPC* ai)
{
	
}
#pragma endregion sit

#pragma region
Pickup* Pickup::Instance()
{
	static Pickup instance;

	return &instance;
}

void Pickup::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Pickup::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sitValue = 0;

	if(distance < 30)//some randon number
	{
		//pickup the object

		//wait x amount of time, then transition
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Pickup::Exit(NPC* ai)
{
	
}
#pragma endregion pickup

#pragma region

Talk* Talk::Instance()
{
	static Talk instance;

	return &instance;
}

void Talk::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Talk::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float talkValue = 0;

	if(distance < 30)//some randon number
	{
		vector<Affordance> affordances = ai->getAffordances();
		for(auto aff: affordances)
		{
			
			if(aff.getTag() == talk)
			{
				talkValue = aff.getValue();
			}
		}
		//give brain values
		ai->getBrain()->ExternalStimuli(talk, talkValue);
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Talk::Exit(NPC* ai)
{
	
}


#pragma endregion talk

#pragma region
Toilet* Toilet::Instance()
{
	static Toilet instance;

	return &instance;
}

void Toilet::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Toilet::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float toiletValue = 0;

	if(distance < 30)//some randon number
	{
		vector<Affordance> affordances = ai->getAffordances();
		for(auto aff: affordances)
		{
			if(aff.getTag() == toilet)
			{
				toiletValue = aff.getValue();
			}
		}
		//give brain values
		ai->getBrain()->ExternalStimuli(talk, toiletValue);
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Toilet::Exit(NPC* ai)
{
	
}
#pragma endregion toilet

#pragma region

SleepState* SleepState::Instance()
{
	static SleepState instance;

	return &instance;
}

void SleepState::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);
	*/
}

void SleepState::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 100)//some randon number
	{
		vector<Affordance> affordances = ai->getAffordances();
		for(auto aff: affordances)
		{
			if(aff.getTag() == sleep)
			{
				sleepValue = aff.getValue();
			}
		}
		//give brain values
		ai->getBrain()->ExternalStimuli(sleep, sleepValue);
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void SleepState::Exit(NPC* ai)
{
	
}


#pragma endregion sleep


#pragma region
Throw* Throw::Instance()
{
	static Throw instance;

	return &instance;
}

void Throw::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Throw::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 30)//some randon number
	{
		//throw the object

		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Throw::Exit(NPC* ai)
{
	
}
#pragma endregion throw

#pragma region
Touch* Touch::Instance()
{
	static Touch instance;

	return &instance;
}

void Touch::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Touch::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 30)//some randon number
	{
		//touch the object

		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Touch::Exit(NPC* ai)
{
	
}
#pragma endregion touch

#pragma region
Climb* Climb::Instance()
{
	static Climb instance;

	return &instance;
}

void Climb::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Climb::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 30)//some randon number
	{
		//climb the object?

		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Climb::Exit(NPC* ai)
{
	
}
#pragma endregion climb

#pragma region
Push* Push::Instance()
{
	static Push instance;

	return &instance;
}

void Push::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Push::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 5)//some randon number
	{
		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Push::Exit(NPC* ai)
{
	
}
#pragma endregion push

#pragma region
Pull* Pull::Instance()
{
	static Pull instance;

	return &instance;
}

void Pull::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Pull::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 30)//some randon number
	{
		//pull the object

		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Pull::Exit(NPC* ai)
{
	
}
#pragma endregion pull

#pragma region
Vendor* Vendor::Instance()
{
	static Vendor instance;

	return &instance;
}

void Vendor::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Vendor::Execute(NPC* ai)
{
	walkTo(ai, ai->getTarget());
	Vec3 targetPos = ai->getTarget()->getPos();
	Vec3 aiPos = ai->getPos();

	float distance = (targetPos - aiPos).length();
	float sleepValue = 0;

	if(distance < 30)//some randon number
	{
		//buy from the vendor

		ai->getStatemachine()->ChangeState(Wander::Instance());
	}
}

void Vendor::Exit(NPC* ai)
{
	
}
#pragma endregion vendor

#pragma region
Place* Place::Instance()
{
	static Place instance;

	return &instance;
}

void Place::Enter(NPC* ai)
{
	//ai->setState(3);
	/**
	ai->getShip()->setChased(true);*/
}

void Place::Execute(NPC* ai)
{

	//walkTo(ai, ai->targe
	/**
	const float PI = 3.141592654f;
	float yrotrad = ((ai->getShip()->getRotation() / 180) * PI);
	Vec3 d1,d2;
	d1.setX(float(sin(yrotrad)));
	d1.setZ(float(cos(yrotrad)));
	d2.setX(((MainPlayer*)EntityManager::Instance()->getEntity(0))->getPos().getX()-ai->getShip()->getPos().getX());
	d2.setZ(((MainPlayer*)EntityManager::Instance()->getEntity(0))->getPos().getZ()-ai->getShip()->getPos().getZ());
	float a = acos(d1*d2/(d2.length()*d1.length()));
	if(a>0.09)
	{
		if(d1.xProd(d2).getY()>0)ai->getShip()->rotate(-ai->getShip()->getRotateSpeed());
		if(d1.xProd(d2).getY()<0)ai->getShip()->rotate(ai->getShip()->getRotateSpeed());
	}
	else
	{
		if(ai->getShip()->getSpeed() < ai->getShip()->getMaxSpeed())
		{
			ai->getShip()->setSpeed(ai->getShip()->getSpeed()+ai->getShip()->getAccel());//making the ship speed up to max speed
		}
		else if(ai->getShip()->getSpeed() > ai->getShip()->getMaxSpeed())
		{
			ai->getShip()->setSpeed(ai->getShip()->getMaxSpeed());//making it slow to the max speed
		}
	}

	ai->nextTarget();

	float length = (ai->getShip()->getPos() - ((MainPlayer*)EntityManager::Instance()->getEntity(0))->getPos()).length();

	if(length > 500)
	{
		ai->GetFSM()->ChangeState(Goto::Instance());
	}*/
}

void Place::Exit(NPC* ai)
{
	
}
#pragma endregion place

#pragma region
Wander* Wander::Instance()
{
	static Wander instance;

	return &instance;
}

void Wander::Enter(NPC* ai)
{
	
	wanderTarget = findNewTarget(ai);
}

void Wander::Execute(NPC* ai)
{
	walkTo(ai, wanderTarget);

	Vec3 aiPos = ai->getPos();

	float distance = (wanderTarget - aiPos).length();
	float foodValue = 0;

	if(distance < 30)//some randon number
	{
		wanderTarget = findNewTarget(ai);
	}
}

void Wander::Exit(NPC* ai)
{
	
}
#pragma endregion wander






