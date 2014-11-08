#pragma once



class ElapsedTimecontrol
{
public:
    static ElapsedTimecontrol * Instance();
    float GetElapsedTime() const;
	float GetCurrentTimef() const;
	
private:
	ElapsedTimecontrol( float maxTimeStep);
    float m_fMaxTimeStep;
    mutable float m_fPrevious;
};
