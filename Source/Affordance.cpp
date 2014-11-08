#include "Affordance.h"

Affordance::Affordance()
{
	m_value = 0;
	m_description = Tag::wander;
}

void Affordance::setTag(Tag description)
{
	m_description = description;
}

void Affordance::setTag(std::string description)
{// iterate through all tags
	if(find_first(description, "eat"))
	{
		m_description = Tag::eat;
	}
	else if(find_first(description, "drink"))
	{
		m_description = Tag::drink;
	}
	else if(find_first(description, "sit"))
	{
		m_description = Tag::sit;
	}
	else if(find_first(description, "pickup"))
	{
		m_description = Tag::pickup;
	}
	else if(find_first(description, "talk"))
	{
		m_description = Tag::talk;
	}
	else if(find_first(description, "toilet"))
	{
		m_description = Tag::toilet;
	}
	else if(find_first(description, "sleep"))
	{
		m_description = Tag::sleep;
	}
	else if(find_first(description, "throwable"))
	{
		m_description = Tag::throwable;
	}
	else if(find_first(description, "touch"))
	{
		m_description = Tag::touch;
	}
	else if(find_first(description, "climb"))
	{
		m_description = Tag::climb;
	}
	else if(find_first(description, "push"))
	{
		m_description = Tag::push;
	}
	else if(find_first(description, "pull"))
	{
		m_description = Tag::pull;
	}
	else if(find_first(description, "vendor"))
	{
		m_description = Tag::vendor;
	}
	else if(find_first(description, "toxic"))
	{
		m_description = Tag::toxic;
	}
	else if(find_first(description, "wander"))
	{
		m_description = Tag::wander;
	}
}

Tag Affordance::getTag() const
{
	return(m_description);
}



void Affordance::setValue(float value)
{
	m_value = value;
	// clamp to 0 if <
	if(m_value < 0)
	{
		m_value = 0;
	}
	
	// clamp to 1 if >
	if(m_value > 1)
	{
		m_value = 1;
	}
}

float Affordance::getValue() const
{
	return(m_value);
}

std::string Affordance::tagToString(Tag t)
{
	if(t == Tag::eat)
	{
		return "eat";
	}
	else if(t == Tag::drink)
	{
		return "drink";
	}
	else if(t == Tag::sit)
	{
		return "sit";
	}
	else if(t == Tag::pickup)
	{
		return "pickup";
	}
	else if(t == Tag::talk)
	{
		return "talk";
	}
	else if(t == Tag::toilet)
	{
		return "toilet";
	}
	else if(t == Tag::sleep)
	{
		return "sleep";
	}
	else if(t == Tag::throwable)
	{
		return "throwable";
	}
	else if(t == Tag::touch)
	{
		return "touch";
	}
	else if(t == Tag::climb)
	{
		return "climb";
	}
	else if(t == Tag::push)
	{
		return "push";
	}
	else if(t == Tag::pull)
	{
		return "pull";
	}
	else if(t == Tag::vendor)
	{
		return "vendor";
	}
	else if(t == Tag::toxic)
	{
		return "toxic";
	}
	else if(t == Tag::wander)
	{
		return "wander";
	}

	return "none";
}


State<NPC>*  Affordance::tagToState(Tag t)
{
	switch(t)
	{
	case eat:
		return Eat::Instance();
		break;
	case drink:
		return Drink::Instance();
		break;
	case sit:
		return Sit::Instance();
	break;
	case pickup:
		return Pickup::Instance();
		break;
	case talk:
		return Talk::Instance();
		break;
	case toilet:
		return Toilet::Instance();
		break;
	case sleep:
		return SleepState::Instance();
		break;
	case throwable:
		return Throw::Instance();
		break;
	case touch:
		return Touch::Instance();
		break;
	case climb:
		return Climb::Instance();
		break;
	case push:
		return Push::Instance();
		break;
	case pull:
		return Pull::Instance();
		break;
	case vendor:
		return Vendor::Instance();
		break;
	default:
		return Wander::Instance();
		break;
	}
}