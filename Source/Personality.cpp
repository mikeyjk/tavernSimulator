#include "Personality.h"
#include <iostream>
#include "ControlSystem.h"

Personality::Personality()
{
	//Init of thresholds
	HVThreshold.initHumanValues(&HVThreshold, 40);
	HVDynamics.initHumanValues(&HVDynamics, 25);
	HVDynamics.Phys.Agile = HVThreshold.Phys.Agile;
	HVDynamics.Phys.Sight = HVThreshold.Phys.Sight;
	HVDynamics.Phys.Stomach = HVThreshold.Phys.Stomach;
	HVDynamics.Phys.Strength = HVThreshold.Phys.Strength;
	HVDynamics.Phys.Health = HVThreshold.Phys.Health;
	BladderMod = 1;

	calculateStrength();
	calculateAgility();
	calculateSight();
	determineEmotion();
	Emotion = calcEnEmotion();

	dTime = 0;
}

//public caller to add trait
void Personality::addTrait(std::string key)
{
	stTrait tr = Traits::Instance()->getTrait(key);
	if(tr.name != "empty")
	{
		addTrait(tr);
	}
}

// private mutator of threshold
bool Personality::addTrait(stTrait Tr)
{
	HVThreshold.Ment.Boredom += Tr.HV.Ment.Boredom;
	HVThreshold.Ment.Curiosity += Tr.HV.Ment.Curiosity;
	HVThreshold.Ment.Fear += Tr.HV.Ment.Fear;
	HVThreshold.Ment.Memory += Tr.HV.Ment.Memory;
	HVThreshold.Ment.Talk += Tr.HV.Ment.Talk;

	HVThreshold.Phys.Agile += Tr.HV.Phys.Agile;
	HVThreshold.Phys.Sight += Tr.HV.Phys.Sight;
	HVThreshold.Phys.Stomach += Tr.HV.Phys.Stomach;
	HVThreshold.Phys.Strength += Tr.HV.Phys.Strength;
	HVThreshold.Phys.Health += Tr.HV.Phys.Health;

	HVThreshold.Vit.Bladder += Tr.HV.Vit.Bladder;
	HVThreshold.Vit.Hunger += Tr.HV.Vit.Hunger;
	HVThreshold.Vit.Thirst += Tr.HV.Vit.Thirst;
	HVThreshold.Vit.Tiredness += Tr.HV.Vit.Tiredness;
	HVThreshold.Vit.Toxication += Tr.HV.Vit.Toxication;
	myTraits.push_back(Tr);

	return true;
}




void Personality::update(double deltaTime)
{
	dTime += deltaTime;
	//every 5 seconds there is an update to the vital dynamic values
	if(dTime >= 5)
	{
		HVDynamics.Vit.Hunger ++;
		if(HVDynamics.Vit.Hunger > 100)
			HVDynamics.Vit.Hunger = 100;

		HVDynamics.Vit.Thirst += 0.5f;
		if(HVDynamics.Vit.Thirst > 100)
			HVDynamics.Vit.Thirst = 100;

		HVDynamics.Vit.Tiredness += 0.2;
		if(HVDynamics.Vit.Tiredness > 100)
			HVDynamics.Vit.Tiredness = 100;

		//bladder will slowly increase regardless of how often they drink
		if(BladderMod > 1)
		{
			BladderMod -= -.5;
			if(BladderMod < 1)
				BladderMod = 1;
		}
		HVDynamics.Vit.Bladder += (0.05 * BladderMod);
		if(HVDynamics.Vit.Bladder > 100)
			HVDynamics.Vit.Bladder = 100;
		//if the AI is scared then thier fear will slowly fall
		if(checkFear())
		{
			HVDynamics.Ment.Fear --;
		}

		HVDynamics.Ment.Talk += 0.6;
		if(HVDynamics.Ment.Talk > 100)
			HVDynamics.Ment.Talk = 100;

		HVDynamics.Ment.Boredom += 0.1;
		if(HVDynamics.Ment.Boredom > 100)
			HVDynamics.Ment.Boredom = 100;



		calculateStrength();
		calculateAgility();
		calculateSight();
		determineEmotion();
		Emotion = calcEnEmotion();
		dTime = 0;
	}

	
}

void Personality::printValues()
{
	std::cout	<< "Hunger: " << HVDynamics.Vit.Hunger << "/" << HVThreshold.Vit.Hunger 
				<<" --  Thirst: "<< HVDynamics.Vit.Thirst << "/" << HVThreshold.Vit.Thirst 
				<<" --  Tired: "<< HVDynamics.Vit.Tiredness << "/" << HVThreshold.Vit.Tiredness 
				<<" --  Strength: "<< HVDynamics.Phys.Strength << "/" << HVThreshold.Phys.Strength
				<<" --  Agility: "<< HVDynamics.Phys.Agile << "/" << HVThreshold.Phys.Agile<< std::endl;
}

#pragma region
bool Personality::checkHunger()
{
	if(HVDynamics.Vit.Hunger > HVThreshold.Vit.Hunger)
	{
		std::cout << "IM HUNGRY!!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkThirst()
{
	if(HVDynamics.Vit.Thirst > HVThreshold.Vit.Thirst)
	{
		std::cout << "IM THIRSTY!!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkTired()
{
	if(HVDynamics.Vit.Tiredness > HVThreshold.Vit.Tiredness)
	{
		std::cout << "IM SLEEPY!!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkBladder()
{
	if(HVDynamics.Vit.Bladder > HVThreshold.Vit.Bladder)
	{
		std::cout << "WHERE IS A TOILET!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkToxication()
{
	if(HVDynamics.Vit.Toxication > HVThreshold.Vit.Toxication)
	{
		std::cout << "IM DRUNK!!!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkFear()
{
	if(HVDynamics.Ment.Fear > HVThreshold.Ment.Fear)
	{
		std::cout << "IM SCARED!!!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkBoredom()
{
	if(HVDynamics.Ment.Boredom > HVThreshold.Ment.Boredom)
	{
		std::cout << "IM BORED!!!!" << std::endl;
		return true;
	}
	return false;
}
bool Personality::checkTalk()
{
	if(HVDynamics.Ment.Talk > HVThreshold.Ment.Talk)
	{
		std::cout << "IM NEED TO TALK!!!!" << std::endl;
		return true;
	}
	return false;
}

#pragma endregion Value Checks


#pragma region
bool Personality::ExternalStimuli(Tag name, float f, float tox)
{
	if(f < 1.0 && f > 0.0)
	{
		f = f * 100;
	}

	if(tox < 1.0 && tox > 0.0)
	{
		tox = tox * 100;
	}

	switch(name)
	{
	case eat:
		reduceHunger(f);
		reduceBoredom(10);
		return true;
		break;
	case drink:
		reduceThirst(f);
		reduceBoredom(10);
		reduceToxication(-tox);
		return true;
		break;
	case toilet:
		reduceBladder(f);
		reduceBoredom(5);
		return true;
		break;
	case sleep:
		reduceTired(f);
		reduceBoredom(5);
		return true;
		break;
	case talk:
		reduceTalk(f);
		reduceBoredom(15);
		return true;
		break;
	default:
		return false;
		break;
	}
}

void Personality::addFear(float f)
{
	HVDynamics.Ment.Fear += f;
}
void Personality::addBoredom(float f)
{
	HVDynamics.Ment.Boredom += f;
}
void Personality::reduceHunger(float f){
	HVDynamics.Vit.Hunger -= f;
	if(HVDynamics.Vit.Hunger < 0)
		HVDynamics.Vit.Hunger = 0;
}
void Personality::reduceThirst(float f){
	HVDynamics.Vit.Thirst -= f;
	if(HVDynamics.Vit.Thirst < 0)
		HVDynamics.Vit.Hunger = 0;
	BladderMod = f / 10;
}
void Personality::reduceTired(float f){
	HVDynamics.Vit.Tiredness -= f;
	if(HVDynamics.Vit.Tiredness < 0)
		HVDynamics.Vit.Tiredness = 0;
}
void Personality::reduceBladder(float f){
	HVDynamics.Vit.Bladder -= f;
	if(HVDynamics.Vit.Bladder < 0)
		HVDynamics.Vit.Bladder = 0;
}
void Personality::reduceToxication(float f){
	HVDynamics.Vit.Toxication -= f;
	if(HVDynamics.Vit.Toxication < 0)
		HVDynamics.Vit.Toxication = 0;
}
void Personality::reduceTalk(float f){
	HVDynamics.Ment.Talk -= f;
	if(HVDynamics.Ment.Talk < 0)
		HVDynamics.Ment.Talk = 0;
}
void Personality::reduceBoredom(float f)
{
	HVDynamics.Ment.Boredom -= f;
	if(HVDynamics.Ment.Boredom < 0)
		HVDynamics.Ment.Boredom = 0;
}
void Personality::reduceCuriosity(float f)
{
	HVDynamics.Ment.Curiosity -= f;
	if(HVDynamics.Ment.Curiosity < 0)
		HVDynamics.Ment.Curiosity = 0;
}
void Personality::reduceFear(float f)
{
	HVDynamics.Ment.Fear -= f;
	if(HVDynamics.Ment.Fear < 0)
		HVDynamics.Ment.Fear = 0;
}

#pragma endregion External Stimuli

#pragma region
void Personality::calculateStrength()
{
	//Strength is determined by hunger and thirst. The hungrier and thirstier the NPC is, the weaker they will be.
	HVDynamics.Phys.Strength = HVThreshold.Phys.Strength - (HVThreshold.Phys.Strength * (((HVDynamics.Vit.Hunger + HVDynamics.Vit.Thirst)/2)/100));
}
void Personality::calculateAgility()
{
	//Agility is determined by hunger and Tiredness. The hungrier and Tireder the NPC is, the slower they will be.
	HVDynamics.Phys.Agile = HVThreshold.Phys.Agile - (HVThreshold.Phys.Agile * (((HVDynamics.Vit.Hunger + HVDynamics.Vit.Tiredness) /2) / 100));

	//if intoxicated then update agility again
	if(HVDynamics.Vit.Toxication > 20)
	{//if the AI is beginning to get intoxicated they will lose agility more rapidly (speed and dodging) 
		HVDynamics.Phys.Agile = HVThreshold.Phys.Agile - (HVThreshold.Phys.Agile * (((HVDynamics.Vit.Hunger + HVDynamics.Vit.Toxication + HVDynamics.Vit.Tiredness)/3)/100));
	}
}
void Personality::calculateSight()
{
	//Sight is determined by toxication and tiredness. The drunker and sleepier the NPC is, the less sight range they will have.
	HVDynamics.Phys.Sight = HVThreshold.Phys.Sight - (HVThreshold.Phys.Sight * ( (HVDynamics.Vit.Tiredness + HVDynamics.Vit.Toxication)/2 ) /100 );
}
float Personality::determineEmotion()
{
	int count = 0;
	if(checkHunger())
	{
		count++;
	}
	if(checkThirst())
	{
		count++;
	}
	if(checkBladder())
	{
		count++;
	}
	if(checkTired())
	{
		count++;
	}
	if(checkFear())
	{
		count++;
	}
	if(checkBoredom())
	{
		count++;
	}
	if(checkTalk())
	{
		count++;
	}
	if(checkToxication())
	{
		count++;
	}

	HVDynamics.Ment.Emotion = count * 10;
	return HVDynamics.Ment.Emotion;
}
enEmotion Personality::calcEnEmotion()
{
	float posRange = HVThreshold.Ment.Emotion / 4;
	float negRange = (80 - HVThreshold.Ment.Emotion) / 4;

	float currEmotion = HVDynamics.Ment.Emotion;
	float midPoint = HVThreshold.Ment.Emotion;

	//positive range
	if(currEmotion >= 0 && currEmotion < posRange)
	{
		return Esctatic;
	}
	else if(currEmotion >= posRange && currEmotion < 2 * posRange)
	{
		return Joy;
	}
	else if(currEmotion >= 2*posRange && currEmotion < 3 * posRange)
	{
		return Happy;
	}
	else if(currEmotion >= 3*posRange && currEmotion < 4 * posRange)
	{
		return Fine;
	}

	//SMACK BANG IN THE MIDDLE
	else if(currEmotion = midPoint)
	{
		return Complacent;
	}

	else if(currEmotion >= midPoint && currEmotion < midPoint + negRange)
	{
		return Sad;
	}
	else if(currEmotion >= midPoint + negRange && currEmotion < midPoint + (2*negRange))
	{
		return Desolate;
	}
	else if(currEmotion >= midPoint + (2*negRange) && currEmotion < midPoint + (3*negRange))
	{
		return Angry;
	}
	else if(currEmotion >= midPoint + (3*negRange) && currEmotion < midPoint + (4*negRange))
	{
		return Rage;
	}
	else
		return noEmotion;
}
#pragma endregion internal calculations



std::vector<Tag> Personality::getNeeds()
{
	std::vector<Tag> needs;

	// DEBUG: TEST AFFORDANCE
	//needs.push_back(Tag::push);

	if(HVDynamics.Vit.Hunger > HVThreshold.Vit.Hunger)
	{
		needs.push_back(Tag::eat);
	}

	if(HVDynamics.Vit.Thirst > HVThreshold.Vit.Thirst)
	{
		needs.push_back(Tag::drink);
	}

	if(HVDynamics.Vit.Tiredness > HVThreshold.Vit.Tiredness)
	{
		needs.push_back(Tag::sleep);
	}

	if(HVDynamics.Vit.Bladder > HVThreshold.Vit.Bladder)
	{
		needs.push_back(Tag::toilet);
	}

	if(HVDynamics.Vit.Toxication > HVThreshold.Vit.Toxication)
	{
		needs.push_back(Tag::toilet);
	}

	if(HVDynamics.Ment.Boredom > HVThreshold.Ment.Boredom )
	{
		needs.push_back(Tag::wander);
	}

	if(HVDynamics.Ment.Talk > HVThreshold.Ment.Talk )
	{
		needs.push_back(Tag::talk);
	}

	if(HVDynamics.Ment.Curiosity > HVThreshold.Ment.Curiosity )
	{
	}

	return needs;
}

float Personality::getSight()
{
	return(HVDynamics.Phys.Sight);
}

float Personality::getSpeed()
{
	return HVDynamics.Phys.Agile;
}

void Personality::giveHudData()
{
	ControlSystem::Instance()->hud.giveHudHVData(&HVDynamics, &HVThreshold, myTraits, &Emotion);
}

void Personality::giveHudMoreData(int npcid, std::string state, std::vector<std::string> needs, std::vector<int> affordable)
{
	ControlSystem::Instance()->hud.giveHudNPCData(npcid, state, needs, affordable);
}