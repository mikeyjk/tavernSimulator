#ifndef HUD_H
#define HUD_H

/**
	*@class HUD
	*@brief The Class that is renderable by the rendering engine with all HUD elements.
	*@author:  Karl Tysoe
	*@inherits:  I_DrawableObject
	*@Used By:  Game System, Rendering Engine;    
	*@date 26/03/2014
	*
*/

#include "I_DrawableObject.h"
#include "Global_Structs.h"
#include "Traits.h"
#include "Affordance.h"
#include <vector>

class RenderingEngine;
class IdGenerator;

class HUD : public I_DrawableObject
{
public:
	/**
		*@brief HUD Constructor
		*
		* This is the basic Constructor
		* Sets the HUD up with its own ID for the rendering engine
		* 
		*@param nil
		*@returns nil
	*/
	HUD();

	/**
		*@brief HUD Destructor
		*
		* This is the basic Destructor
		* 
		*@param nil
		*@returns nil
	*/
	~HUD();

	/**
		*@brief I_DrawableObject Draw function
		*
		* Draws the HUD elements
		* 
		*@param nil
		*@returns nil
	*/
	virtual void Draw();

	void turnOffSplash()
	{
		splash = false;
	}

	bool getSplash()
	{
		return splash;
	}

	void DrawSplash();

	/**
		*@brief I_DrawableObject SetBufferRef function
		*
		* Passes the object to the render engine for rendering
		* 
		*@param nil
		*@returns nil
	*/
	virtual void SetBufferRef();

	/**
		*@brief I_DrawableObject Destroy function
		*
		* takes the object out of the rendering engine
		* 
		*@param nil
		*@returns nil
	*/
	virtual void Destory();

	/**
		*@brief setManual function
		*
		* Sets the boolean isManual to the param provided
		* 
		*@param bool 
		*@returns nil
	*/
	void setManual(bool m);

	/**
		*@brief getManual function
		*
		* returns the bool isManual
		* 
		*@param nil
		*@returns isManual - bool
	*/
	bool getManual();

	/**
		*@brief switchManual function
		*
		* swaps isManual to true if false, or false if true
		* 
		*@param nil
		*@returns nil
	*/
	void switchManual();

	void setExit(bool e){Ex = e;}
	bool getExit(){return Ex;}

	void giveHudNPCData(int npcid, std::string stateName, std::vector<std::string> needs, std::vector<int> afford);

	void giveHudHVData(HumanValues* data, HumanValues* thresh, std::vector<stTrait> tr, enEmotion* emot)
	{
		overlayData = data;
		overlayThreshold = thresh;
		TraitData = tr;
		dispEmotion = emot;
	}

	void giveHudAffordance(std::vector<Affordance> affordances)
	{
		m_affordances = affordances;
	}

private:
	///boolean for control of Manual dispaly
	bool isManual;

	bool Ex;

	std::string enEmotionToString(enEmotion em);

	/// pointer for the IDgenerator
	IdGenerator* IdGen;

	///pointer for the Render Engine
	RenderingEngine* RederingHandle;

	///ID int
	unsigned int m_objectID;
	

	//For Debugging
	HumanValues* overlayData;
	HumanValues* overlayThreshold;
	std::vector<stTrait> TraitData;
	std::vector<Affordance> m_affordances;
	enEmotion* dispEmotion;
	std::vector<std::string> needs;
	std::vector<int> afforded;
	std::string stateName;
	int npcid;

	bool splash;
};

#endif