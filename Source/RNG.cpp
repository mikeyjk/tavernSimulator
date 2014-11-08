#include "RNG.h"
#include <time.h>

	RNG* RNG::Instance()
	{
		static RNG Instance;
		return &Instance;
	}



	RNG::RNG()
	{

	}

	RNG::RNG(string seed)
	{
		int total = 0;
		for each(char c in seed)
		{
			int cI = (int)c;
			total += cI;
		}

		srand (total); 
		this->seed = seed;
	}

	void RNG::setSeed(string seed)
	{
		int total = 0;
		for each(char c in seed)
		{
			int cI = (int)c;
			total += cI;
		}

		srand (total); 
		this->seed = seed;
	}

	void RNG::randomSeed()
	{
		int s = time(NULL);
		char buffer[50];
		sprintf(buffer, "%d", s);
		seed = buffer;
		//seed = to_string(s);
		srand(s);
	}

	string RNG::retrieveSeed()
	{
		return seed;
	}

	int RNG::randomInt(int max)
	{
		return rand()%max;
	}

	int RNG::randomIntRange(int min, int max)
	{
		float r = (float)rand() / (float)RAND_MAX;
		return min + r * (max - min);
		//return rand()% max+min;
	}

	float RNG::randomFloat(float max)
	{
		return 1;
	}