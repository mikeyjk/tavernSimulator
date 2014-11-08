#ifndef BRAIN_H
#define BRAIN_H

#include "Personality.h"
//#include "AffordanceSystem.h"
#include <vector>

class Brain
{
public:

	Brain();
	~Brain();

	void update(double deltaTime);

	void initPersonality(std::string tr1, std::string tr2, std::string tr3, std::string tr4);

	void addTrait(std::string tr);

	void setState();

private:
	Personality* PS;
	//AffordanceSystem* AS;
	double queryTimer;

	std::vector<enTag> needs;
};

#endif