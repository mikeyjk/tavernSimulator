#include "Brain.h"
#include "Affordance.h"

Brain::Brain()
{
	queryTimer = 0;
	m_needs.clear();
}

Brain::~Brain()
{

}

void Brain::initPersonality(std::string tr1, std::string tr2, std::string tr3, std::string tr4)
{
	PS = new Personality();

	if(tr1 != "null")
		PS->addTrait(tr1);

	if(tr2 != "null")
		PS->addTrait(tr2);

	if(tr3 != "null")
		PS->addTrait(tr3);

	if(tr4 != "null")
		PS->addTrait(tr4);
}

void Brain::update(double deltaTime)
{
	queryTimer += deltaTime;
	PS->update(deltaTime);

	if(queryTimer >= 5)
	{
		m_needs = PS->getNeeds();
		//query affordance system
	}
}

void Brain::addTrait(std::string tr)
{
	PS->addTrait(tr);
}

void Brain::setState()
{

}

bool Brain::ExternalStimuli(Tag name, float f, float tox)
{
	return PS->ExternalStimuli(name, f*100, tox*100);
}

void Brain::giveAffordancesThatMeetNeeds(vector<GameObject*> aff)
{
	affordanceObjects = aff;
}

GameObject* Brain::calculateTarget(Tag  &findState)
{
	GameObject* target;
	float value = 0;
	findState = wander;
	//This is a quick calculation.. quick as in it hasnt had much though. Just finds the highest value affordance that meets a need and goes for it.
	//doesnt care about what need is the biggest need.. IE Thirst should be most important.. Then Food.. Then sleep etc.. 
	for(auto need: m_needs)
	{
		for(auto obj : affordanceObjects)
		{
			for(auto aff : obj->getAffordances())
			{
				if(aff.getTag() == need)
				{
					if(aff.getValue() > value)
					{
						target = obj;
						findState = need;
					}
				}
			}
		}
	}

	return target;
}

std::vector<std::string> Brain::getNeedsStr()
{
	std::vector<std::string> needs;

	for(auto& need : m_needs)
	{
		needs.push_back(Affordance::tagToString(need));
	}

	return(needs);
}

