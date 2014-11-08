#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <iostream>

class Timer
{
public:

Timer()
{
	CPUStartTimer();
}

void CPUStartTimer()
{
	init = clock();
	currTime = init;
}

void CPUEndTimer()
{
	finalTime=clock()-init;
}

void updateTime()
{
	lastTime = currTime;
	currTime = clock();
	deltaTime = currTime - lastTime;
}

float CPUGetTimePassed()
{
	return (double)(currTime - init) / ((double)CLOCKS_PER_SEC);
}

float getDeltaTime()
{
	return deltaTime / ((double)CLOCKS_PER_SEC);
}

private:
clock_t init, finalTime, lastTime, deltaTime, currTime;
};

#endif