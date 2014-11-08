#include "IdGenerator.h"


IdGenerator* IdGenerator::Instance()
{
	static IdGenerator Instance;
	return &Instance;
}


IdGenerator::IdGenerator(void)
{
	ID = 0;
}


IdGenerator::~IdGenerator(void)
{
}


unsigned int IdGenerator::GetID()
{
	ID++;
	return ID;
}