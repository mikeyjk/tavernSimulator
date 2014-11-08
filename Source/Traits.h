#ifndef TRAITS_H
#define TRAITS_H


/**
		* @class Trait
		* @brief This class contains all of the stTrait values that can be added to the Human Value Threshold
		* A trait uses the Human Values structure
		* It simple adds a modifier to the threshold levels for a personality
		* example, Social takes longer to get intoxicated, needs to talk more often and is thirsty more often.
		*
		* Traits is a singleton class, as there is only ever need for one instance of it.
		* 
		* @todo: Make more trait types.
		* @todo: Make a script loader so that traits can be defined in script rather than in the constructor
		* @author Karl
		* @version 01
		* @date 15/10/2014
     */

#include "Global_Structs.h"
#include <map>
#include <string>

/// stTrait is just a small encapsulation of HumanValues to add the name string
struct stTrait
{
	HumanValues HV;
	std::string name;
};

class Traits
{
public:
	/**
		*@brief Instance function
		*
		* This is getter for the singleton of Traits
		* 
		*@param nil
		*@returns Traits* Instance
	*/
	static Traits* Instance()
	{
		static Traits Instance;
		return &Instance;
	}

	/**
		*@brief getTrait function
		*
		* This tries to get the trait from the trait map, or it returns a trait called "empty"
		* 
		*@param key - string
		*@returns trait that correlates to the key
	*/
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

	/**
		*@brief Traits constructor
		*
		* This constructor initialised all of the trait types.
		* to define a new trait, just reset tr to 0s and then add the values you want, give it a name and add it to the trait map
		* 
		*@param nil
		*@returns nil
	*/
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

		// --- LIKES TO DRINK --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "LikesToDrink";
		tr.HV.Vit.Toxication = 20;
		tr.HV.Vit.Thirst = -20;
		insertToTraitMap(tr.name, tr);

		// --- LIKES TO EAT --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "LikesToEat";
		tr.HV.Vit.Hunger = -20;
		tr.HV.Phys.Stomach = 20;
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

		// --- CHEERFUL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Cheerful";
		tr.HV.Ment.Emotion = 15;
		insertToTraitMap(tr.name, tr);

		// --- DEPRESSED --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Depressed";
		tr.HV.Ment.Emotion = 15;
		insertToTraitMap(tr.name, tr);

		// --- FORGETFUL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Forgetful";
		tr.HV.Ment.Memory = -10;
		insertToTraitMap(tr.name, tr);

		// --- SLEEPY --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "Sleepy";
		tr.HV.Vit.Tiredness =-15;
		insertToTraitMap(tr.name, tr);

		// --- NIGHTOWL --- //
		tr.HV.initHumanValues(&tr.HV, 0);
		tr.name = "NightOwl";
		tr.HV.Vit.Tiredness = 15;
		insertToTraitMap(tr.name, tr);
	}


	/**
		*@brief insertTotraitMap function
		*
		* simple wrap of dictionary insert.. because im lazy..
		* 
		*@param str - string, tr - stTrait
		*@returns nil
	*/
	void insertToTraitMap(std::string str, stTrait tr)
	{
		allTraits.insert(std::pair<std::string, stTrait>(str, tr));
	}

	/// needs a vector of traits... personality addTrait function asks traits for that trait and adds it.
	std::map<std::string, stTrait> allTraits;
	
};

#endif
