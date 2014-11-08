#include "Brain.h"

Brain::Brain()
{
	queryTimer = 0;
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

	if(queryTimer >= 5)
	{
		needs = PS->getNeeds();
		//query affordance system
	}

	PS->update(deltaTime);
}

void Brain::addTrait(std::string tr)
{

}

void Brain::setState()
{

}