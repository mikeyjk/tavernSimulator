#include "AffordanceSystem.h"

AffordanceSystem* AffordanceSystem::Instance()
	{
		static AffordanceSystem Instance;
		return &Instance;
	}

