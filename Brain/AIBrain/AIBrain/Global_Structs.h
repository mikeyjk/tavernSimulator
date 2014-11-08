#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

struct Physical{
	//These values dynamically start high and drop.
	float Strength;
	float Agile;
	float Stomach;
	float Sight;
	float Health;
};

struct Vital{
	//these values start low and rise
	float Tiredness;
	float Hunger;
	float Thirst;
	float Bladder;
	float Toxication;
};

struct Mental{
	//these values start low and rise
	float Memory;//maybe not needed in here
	float Talk;
	float Curiosity;
	float Boredom;
	float Fear;
	float Emotion;
};

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

enum enTag
{
	eat,
	drink,
	sit,
	pickup,
	attack,
	run,
	talk,
	investigate,
	toilet,
	sleep,
	wander //NOT AN ACTUAL TAG FOR AN ENTITY, JUST USED FOR DETERMINING BOREDOM.
};

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



#endif
