#ifndef AFFORDANCE_H
#define AFFORDANCE_H

#include "Global_Structs.h"

#include <iostream> // solely debugging
#include <string> // description setter
#include <boost/algorithm/string.hpp> // find_first
#include <boost/lexical_cast.hpp> // string -> tag enum
#include "AIOwnedStates.h"
//#include "NPC.h"

//class State;
class NPC;

using namespace boost;

/**
  * @Class Affordance
  * @Summary Represents a single affordance value for an entity.
  *
  *
  */
class Affordance 
{
	private:
		
		Tag m_description; // type of affordance
		
		float m_value; // 0.0 - 0.55 - 1.0 range (100%)

	public:

		Affordance();

		void setTag(Tag description);

		void setTag(std::string description);

		Tag getTag() const;

		void setValue(float value);

		float getValue() const;

		static Tag stringToTag(std::string t);

		static std::string tagToString(Tag t);

		static State<NPC>*  tagToState(Tag t);
};

#endif // AFFORDANCE_H