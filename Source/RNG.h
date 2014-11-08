#ifndef RNG_H
#define RNG_H

#include <String>

using namespace std;

class RNG
{
public:

	static RNG* Instance();

	
	RNG(string seed);

	void setSeed(string seed);
	void randomSeed();

	string retrieveSeed();

	int randomInt(int max);
	int randomIntRange(int min, int max);
	float randomFloat(float max);
	
private:
	RNG();
	string seed;

};

#endif