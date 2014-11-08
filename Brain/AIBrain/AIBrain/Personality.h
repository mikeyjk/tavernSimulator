#ifndef PERSONALITY_H
#define PERSONALITY_H

#include <vector>
#include "Traits.h"
#include "Global_Structs.h"





class Personality
{
public:

	Personality();
	~Personality(){};

	///Update function
	///All values in the HV struct will be updated dynamically inside the
	///update function. They will update at thier own independent times, depending on only itself.
	///traits will affect how things are interpereted and how things get updated
	/// The Threshold value is used to determine HOW fast something will update.
	/// All Physical values are calculated out from a combination of Vital or Mental values
	void update(double deltaTime);


	

	

	//CAN BE ADDED BY OUTSIDE THINGS
	///fear is sent in from the brain
	void addFear(float f);
	///boredom is sent in from the brain
	void addBoredom(float f);

	//ALL THESE VALUES CAN BE REDUCED BY OUTSIDE THINGS
	void reduceHunger(float f);
	void reduceThirst(float f);
	void reduceTired(float f);
	void reduceBladder(float f);
	void reduceToxication(float f);
	void reduceTalk(float f);
	void reduceBoredom(float f);
	void reduceCuriosity(float f);
	void reduceFear(float f);

	/// THis function returns a numberical value that represents the current anger level
	/// it is purely derived from the amount of thresholds that have been passed *  10
	float determineEmotion();

	enEmotion getEnEmotion();



	///Traits get added to the threshold value.
	void addTrait(std::string key);

	///just a vector of tag like items probably change it to enTag
	std::vector<enTag> getNeeds();
	
	


private:

	bool addTrait(stTrait Tr);

	///might be deprecated
	bool checkHunger();
	bool checkThirst();
	bool checkTired();
	bool checkBladder();
	bool checkToxication();
	bool checkFear();
	bool checkBoredom();
	bool checkTalk();
	
	/// Cosmetic function for debugging
	void printValues();

	/// This is what will be compared against for determining when a character needs something
	HumanValues HVThreshold;
	HumanValues HVDynamics;
	double dTime;
	
	//storage of traits.. Mostly for name sake
	//may change to JUST store the name
	//std::vector<stTrait> myTraits;

};

#endif