#ifndef PERSONALITY_H
#define PERSONALITY_H

/**
     * @class Personality
     * @brief This class is the NPCs personality, it controlls the NPCs attributes, and derives its needs
	 * Physical members of the Human Value struct are its attributes (strength, agility, sight, stomach and health)
	 * 
     * @todo: Stomach and Health are currently un-used, as are Fear and Memory
     * @author Karl
     * @version 01
     * @date 15/10/2014
     */

#include <vector>
#include "Traits.h"
#include "Global_Structs.h"

class Personality
{
	public:
		/**
		*@brief Personality Constructor
		*
		* This is the basic Constructor
		* 
		*@param nil
		*@returns nil
	*/
		Personality();

		/**
		*@brief Personality Destructor
		*
		* This is the basic Destructor
		* 
		*@param nil
		*@returns nil
	*/
		~Personality(){};

		///Update function
		///

		/**
		*@brief Update Function
		*
		* All values in the HV struct will be updated dynamically inside the
		* update function. They will update at thier own independent times, depending on only itself.
		* traits will affect how things are interpereted and how things get updated
		* The Threshold value is used to determine HOW fast something will update.
		* All Physical values are calculated out from a combination of Vital or Mental values
		* 
		*@param deltaTime - double
		*@returns nil
	*/
		void update(double deltaTime);

		//CAN BE ADDED BY OUTSIDE THINGS
		
		/**
		*@brief addFear function
		*
		* fear is sent in from the brain
		* 
		*@param f - float
		*@returns nil
		*@post fear is increased
	*/
		void addFear(float f);

		/**
		*@brief addBoredom function
		*
		* boredom is sent in from the brain
		* 
		*@param f - float
		*@returns nil
		*@post boredom is increased
	*/
		void addBoredom(float f);

		



		//ALL THESE VALUES CAN BE REDUCED BY OUTSIDE THINGS
		bool ExternalStimuli(Tag name, float f, float tox = 0);

		/**
		*@brief reduceHunger function
		*
		* food value is sent in from the brain, 
		* hunger is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post hunger is decreased
	*/
		void reduceHunger(float f);

		/**
		*@brief reduceThirst function
		*
		* drink value is sent in from the brain, 
		* thirst is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post thirst is decreased
	*/
		void reduceThirst(float f);

		/**
		*@brief reduceTired function
		*
		* sleep value is sent in from the brain, 
		* sleep is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post sleep is decreased
	*/
		void reduceTired(float f);

		/**
		*@brief reduceBladder function
		*
		* bladder value is sent in from the brain, 
		* bladder is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post bladder is decreased
	*/
		void reduceBladder(float f);

		/**
		*@brief reduceToxication function
		*
		* toxication value is sent in from the brain, 
		* toxication is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post toxication is decreased
	*/
		void reduceToxication(float f);

		/**
		*@brief reduceTalk function
		*
		* Talk value is sent in from the brain, 
		* Talk is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post Talk is decreased
	*/
		void reduceTalk(float f);

		/**
		*@brief reduceBoredom function
		*
		* Boredom value is sent in from the brain, 
		* Boredom is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post boredom is decreased
	*/
		void reduceBoredom(float f);

		/**
		*@brief reduceCuriosity function
		*
		* curiosity value is sent in from the brain, 
		* curiosity is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post toxication is decreased
	*/
		void reduceCuriosity(float f);

		/**
		*@brief reduceFear function
		*
		* fear value is sent in from the brain, 
		* fear is reduced by that value
		* 
		*@param f - float
		*@returns nil
		*@post fear is decreased
	*/
		void reduceFear(float f);

		

		/**
		*@brief addTrait function
		*
		* Traits are searched for in the trait map
		* If there ARE correct traits, it adds it to the HVThreshold
		* 
		*@param key - string
		*@returns nil
		*@post calls the addTrait function WITH the correct trait
	*/
		void addTrait(std::string key);

		///just a vector of tag like items probably change it to Tag
		/**
		*@brief getNeeds function
		*
		* returns all the needs that the Personality has from the dynamics/threshold
		* 
		*@param nil
		*@returns vector<Tag>
		*@post returns all the NPC needs
	*/
		std::vector<Tag> getNeeds();


		/**
		*@brief giveHudData function
		*
		* This functions just calls the controlSystem::Instance() and gives the hud the required data for the overlay
		* 
		*@param nil
		*@returns nil
		*@post gives hud data
	*/
		void giveHudData();

		/**
		*@brief giveHudMoreData function
		*
		* This functions just calls the controlSystem::Instance() and gives the hud the required data for the overlay
		* Gives debug data because NPC navigation isnt working
		* 
		*@param int npcid, std::string state, std::vector<std::string> needs, std::vector<int> affordable
		*@returns nil
		*@post gives hud data
	*/
		void giveHudMoreData(int npcid, std::string state, std::vector<std::string> needs, std::vector<int> affordable);
	
		/**
		*@brief getSight function
		*
		* This returns the HVDynamics sight value
		* 
		*@param nil
		*@returns HVDynamics.phys.sight - float
		*@post returns sight value
	*/
		float getSight();

		/**
		*@brief getSpeed function
		*
		* This returns the HVDynamics speed value
		* 
		*@param nil
		*@returns HVDynamics.phys.agility - float
		*@post returns speed value
	*/
		float getSpeed();

	private:

		/**
		*@brief addTrait function
		*
		* 
		* internal addTrait, called by addTrait(key) to actually add the values
		* 
		*@param Tr stTrait
		*@returns nil
		*@post adds the trait values to HVThreshold
	*/
		bool addTrait(stTrait Tr);

		/**
		*@brief check functions
		*
		* all functions just check thier name sake if thier dynamic has passed the threshold it returns true, else it returns false
		* 
		*@param nil
		*@returns bool
		*@post nil
	*/
		bool checkHunger();
		bool checkThirst();
		bool checkTired();
		bool checkBladder();
		bool checkToxication();
		bool checkFear();
		bool checkBoredom();
		bool checkTalk();

		/**
		*@brief calculateStrength function
		*
		* Strength is calculated by adding a combination of values calculated out to provide a % value
		* 
		*@param nil
		*@returns nil
		*@post calculates the dynamic strength value
	*/
		void calculateStrength();

		/**
		*@brief calculateAgility function
		*
		* Agility is calculated by adding a combination of values calculated out to provide a % value
		* 
		*@param nil
		*@returns nil
		*@post calculates the dynamic agility value
	*/
		void calculateAgility();

		/**
		*@brief calculateSight function
		*
		* Sight is calculated by adding a combination of values calculated out to provide a % value
		* 
		*@param nil
		*@returns nil
		*@post calculates the dynamic sight value
	*/
		void calculateSight();


		/**
		*@brief determineEmotion function
		*
		* THis function returns a numberical value that represents the current anger level
		* it is purely derived from the amount of thresholds that have been passed *  10
		* 
		*@param nil
		*@returns float - emotionValue
		*@post calculates the emotion level
	*/
		float determineEmotion();

		/**
		*@brief calcEnEmotion function
		*
		* This calculates out the enEmotion for the brain to use.
		* 
		*@param nil
		*@returns float - emotionValue
		*@post calculates the emotion level
	*/
		enEmotion calcEnEmotion();
	
		/// Cosmetic function for debugging
		void printValues();

		/// This is what will be compared against for determining when a character needs something
		HumanValues HVThreshold;
		///Personalities Live values
		HumanValues HVDynamics;

		///Personalities current emotional level
		enEmotion Emotion;

		///timer for incrementing live values
		double dTime;
	
		//storage of traits.. Mostly for name sake
		//may change to JUST store the name
		std::vector<stTrait> myTraits;

		/// modifier for the bladder value If the NPC has just drunk thier modifier will be higher 
		///so they will need to go to the toilet more often when they drink
		float BladderMod;

};

#endif