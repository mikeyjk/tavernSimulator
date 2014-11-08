#include "Personality.h"
#include <iostream>
#include "Timer.h"

int main()
{
	Personality test;
	test.addTrait("Strong");
	test.addTrait("Social");
	Timer myTime;


	myTime.CPUStartTimer();
	int i = 0;
	test.printValues();

	while(myTime.CPUGetTimePassed() < 1000)
	{
		myTime.updateTime();
		test.update(myTime.getDeltaTime());
		//test.printValues();
		i++;
		//test.printValues();
	};
	

	std::cin.get();
	return 0;
}



