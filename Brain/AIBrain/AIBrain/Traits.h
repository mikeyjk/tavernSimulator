#ifndef TRAITS_H
#define TRAITS_H

///Class Traits
/// A trait uses the Human Values structure
/// It simple adds a modifier to the threshold levels for a personality
/// example, Social takes longer to get intoxicated, needs to talk more often and is thirsty more often
/// 

#include "Global_Structs.h"
#include <map>

#include <string>

#include <iostream>

struct stTrait
{
	HumanValues HV;
	std::string name;
};

class Traits
{
public:
	static Traits* Instance()
	{
		static Traits Instance;
		return &Instance;
	}
	Traits()
	{
		stTrait tr;

		//MAJOR TRAITS
		// --- SOCIAL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Social";
		tr.HV.Vit.Toxication = 20;
		tr.HV.Ment.Talk = -25;
		tr.HV.Vit.Thirst = -20;

		insertToTraitMap(tr.name, tr);

		// --- ANTISOCIAL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "AntiSocial";
		tr.HV.Vit.Toxication = -20;
		tr.HV.Ment.Talk = 25;
		tr.HV.Phys.Stomach = 20;

		insertToTraitMap(tr.name, tr);

		// --- CONSERVATIVE --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Conservative";
		tr.HV.Ment.Talk = 25;
		tr.HV.Ment.Boredom = 20;
		tr.HV.Phys.Strength = -10;
		tr.HV.Ment.Emotion = 10;

		insertToTraitMap(tr.name, tr);

		// --- AGGRESSIVE --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Aggressive";
		tr.HV.Ment.Talk = 10;
		tr.HV.Phys.Strength = 10;
		tr.HV.Ment.Emotion = -10;

		insertToTraitMap(tr.name, tr);


		
		///MINOR TRAITS ( QUIRKS )
		// --- STRONG --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Strong";
		tr.HV.Phys.Strength = 10;

		insertToTraitMap(tr.name, tr);

		// --- WEAK --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Weak";
		tr.HV.Phys.Strength = -10;

		insertToTraitMap(tr.name, tr);

		// --- QUICK TO ANGER --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "QuickToAnger";
		tr.HV.Ment.Emotion = -10;

		insertToTraitMap(tr.name, tr);

		// --- SLOW TO ANGER --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "SlowToAnger";
		tr.HV.Ment.Emotion = 10;

		insertToTraitMap(tr.name, tr);

		// --- FORGETFUL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Forgetful";
		tr.HV.Ment.Memory = -10;

		insertToTraitMap(tr.name, tr);

		// --- SLEEPY --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Sleepy";
		tr.HV.Vit.Tiredness -15;

		insertToTraitMap(tr.name, tr);

		// --- NIGHTOWL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "NightOwl";
		tr.HV.Ment.Memory = 15;

		insertToTraitMap(tr.name, tr);
	}

	//simple wrap of dictionary insert.. because im lazy..
	void insertToTraitMap(std::string str, stTrait tr)
	{
		allTraits.insert(std::pair<std::string, stTrait>(str, tr));
	}

	stTrait getTrait(std::string key)
	{
		stTrait empty;
		empty.name = "empty";
		if(allTraits.find(key) != allTraits.end())
		{
			return allTraits[key];
		}
		
		return empty;
	}

private:

	/// needs a vector of traits... personality addTrait function asks traits for that trait and adds it.
	std::map<std::string, stTrait> allTraits;
	
};

#endif
