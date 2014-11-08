#include "TimerClass.h"
#include <time.h>
#include <algorithm>

ElapsedTimecontrol::ElapsedTimecontrol(float maxTimeStep)
{
	m_fMaxTimeStep = maxTimeStep;
	m_fPrevious = clock()/(float)CLOCKS_PER_SEC;
}


ElapsedTimecontrol* ElapsedTimecontrol::Instance()
{
	static ElapsedTimecontrol Instance(0.33333f);
	return &Instance;
}

float ElapsedTimecontrol::GetElapsedTime() const
{
	float fCurrentTime = clock()/(float)CLOCKS_PER_SEC;
	float fDeltaTime = fCurrentTime - m_fPrevious;
	m_fPrevious = fCurrentTime;
	fDeltaTime = std::min(fDeltaTime, m_fMaxTimeStep);
	return fDeltaTime;
}

float ElapsedTimecontrol::GetCurrentTimef() const
{
	return clock()/(float)CLOCKS_PER_SEC;
}