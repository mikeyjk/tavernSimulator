#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

class GameObject;

///internal HV struct Physical
struct Physical{
	//These values dynamically start high and drop.
	float Strength;
	float Agile;
	float Stomach;
	float Sight;
	float Health;
};

///internal HV struct Vital
struct Vital{
	//these values start low and rise
	float Tiredness;
	float Hunger;
	float Thirst;
	float Bladder;
	float Toxication;
};

///internal HV struct Mental
struct Mental{
	//these values start low and rise
	float Memory;//maybe not needed in here
	float Talk;
	float Curiosity;
	float Boredom;
	float Fear;
	float Emotion;
};

///Human Values struct, used in the Personality class as the main structure for the needs system
struct HumanValues{
	Physical Phys;
	Vital Vit;
	Mental Ment;

	///basic function that initialises the human values structure to all one value
	void initHumanValues(HumanValues* HV, float f)
	{
		HV->Ment.Boredom = f;
		HV->Ment.Curiosity = f;
		HV->Ment.Fear = f;
		HV->Ment.Memory = f;
		HV->Ment.Talk = f;
		HV->Ment.Emotion = f;

		HV->Phys.Agile = f;
		HV->Phys.Sight = f;
		HV->Phys.Stomach = f;
		HV->Phys.Strength = f;
		HV->Phys.Health = f;

		HV->Vit.Bladder = f;
		HV->Vit.Hunger = f;
		HV->Vit.Thirst = f;
		HV->Vit.Tiredness = f;
		HV->Vit.Toxication = f;
	}
};

///enum of the emotion range of the personality system
enum enEmotion
{
	Esctatic, 
	Joy,
	Happy,
	Fine,
	Complacent,
	Sad,
	Desolate,
	Angry,
	Rage,
	noEmotion
};

/// affordances are percieved actions
///complete list of states that can be transitioned into simply by having a need and seeing an object that affords that need
enum Tag // types of affordancse
{
	eat,
	drink,
	sit,
	pickup,
	talk,
	toilet,
	sleep,
	throwable,
	touch,
	climb,
	push,
	pull,
	vendor,
	placeable,
	toxic,
	wander // NOT AN ACTUAL TAG FOR AN ENTITY, JUST USED FOR DETERMINING BOREDOM.
};

#endif
