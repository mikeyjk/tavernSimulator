#ifndef AI_OWNED_STATES_H
#define AI_OWNED_STATES_H

/**
     * @class AI Owned States
     * @brief This Holds all the AI ships states, allows the ship to switch between states as needed
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */


#include "State.h"
#include <stdio.h>
#include "Vec3.h"


class NPC;


#pragma region
/**
     * @class Eat
     * @brief This class is the state for the AI to Eat
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Eat : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Eat* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Eat(){}

  //copy ctor and assignment should be private
  Eat(const Eat&);
  Eat& operator=(const Eat&);
};


#pragma endregion eat



#pragma region

/**
     * @class Drink
     * @brief This class is the state for the AI to Drink
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Drink : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Drink* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Drink(){}

  //copy ctor and assignment should be private
  Drink(const Drink&);
  Drink& operator=(const Drink&);
};


#pragma endregion drink





#pragma region
/**
     * @class Sit
     * @brief This class is the state for the AI to Sit
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Sit : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Sit* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Sit(){}

  //copy ctor and assignment should be private
  Sit(const Sit&);
  Sit& operator=(const Sit&);
};


#pragma endregion sit



#pragma region
/**
     * @class Pickup
     * @brief This class is the state for the AI ships to Pickup
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Pickup : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Pickup* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Pickup(){}

  //copy ctor and assignment should be private
  Pickup(const Pickup&);
  Pickup& operator=(const Pickup&);
};

#pragma endregion pick up



#pragma region
/**
     * @class Talk
     * @brief This class is the state for the AI ships to Talk
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Talk : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Talk* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Talk(){}

  //copy ctor and assignment should be private
  Talk(const Talk&);
  Talk& operator=(const Talk&);
};

#pragma endregion talk

#pragma region
/**
     * @class Talk
     * @brief This class is the state for the AI ships to Talk
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Toilet : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Toilet* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Toilet(){}

  //copy ctor and assignment should be private
  Toilet(const Toilet&);
  Toilet& operator=(const Toilet&);
};

#pragma endregion toilet


#pragma region
/**
     * @class Throw
     * @brief This class is the state for the AI ships to Throw
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class SleepState : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static SleepState* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	SleepState(){}

  //copy ctor and assignment should be private
  SleepState(const SleepState&);
  SleepState& operator=(const SleepState&);
};

#pragma endregion sleep



#pragma region
/**
     * @class Throw
     * @brief This class is the state for the AI ships to Throw
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Throw : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Throw* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Throw(){}

  //copy ctor and assignment should be private
  Throw(const Throw&);
  Throw& operator=(const Throw&);
};


#pragma endregion throw


#pragma region
/**
     * @class Touch
     * @brief This class is the state for the AI ships to Touch
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Touch : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Touch* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Touch(){}

  //copy ctor and assignment should be private
  Touch(const Touch&);
  Touch& operator=(const Touch&);
};

#pragma endregion touch


#pragma region

/**
     * @class Climb
     * @brief This class is the state for the AI ships to Climb
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Climb : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Climb* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Climb(){}

  //copy ctor and assignment should be private
  Climb(const Climb&);
  Climb& operator=(const Climb&);
};

#pragma endregion climb

#pragma region

/**
     * @class Push
     * @brief This class is the state for the AI ships to Push
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Push : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Push* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Push(){}

  //copy ctor and assignment should be private
  Push(const Push&);
  Push& operator=(const Push&);
};

#pragma endregion push

#pragma region
/**
     * @class Pull
     * @brief This class is the state for the AI ships to Pull
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Pull : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Pull* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Pull(){}

  //copy ctor and assignment should be private
  Pull(const Pull&);
  Pull& operator=(const Pull&);
};


#pragma endregion pull

#pragma region
/**
     * @class Vendor
     * @brief This class is the state for the AI to Vendor
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Vendor : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Vendor* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Vendor(){}

  //copy ctor and assignment should be private
  Vendor(const Vendor&);
  Vendor& operator=(const Vendor&);
};
#pragma endregion vendor

#pragma region
/**
     * @class Place
     * @brief This class is the state for the AI to Place
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Place : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Place* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Place(){}

  //copy ctor and assignment should be private
  Place(const Place&);
  Place& operator=(const Place&);
};
#pragma endregion place


#pragma region
/**
     * @class Wander
     * @brief This class is the state for the AI to Wander
     *
     * @author Karl
     * @version 01
     * @date 30/10/2013
     */
class Wander : public State<NPC>{
public:
	/**
     * @brief Instance function
	 *
	 * this is a singleton
	 * creates an instance of the flee state
	 * and returns it to the state machine
     *
	 * @returns flee state
	 * @post returns the flee state
     */
  static Wander* Instance();

  /**
     * @brief Enter function
	 *
	 * Runs any functions that allows the AI to enter the state
     *
	 * 
	 * @post enters the state
     */
  virtual void Enter(NPC* ai);

  /**
     * @brief Execute function
	 *
	 * makes the ship flee from the player
     *
	 * 
	 * @post runs the flee execution
     */
  virtual void Execute(NPC* ai);

  /**
     * @brief Exit function
	 *
	 * runs and functions that allows the AI to exit the state
     *
	 * 
	 * @post exits flee state
     */
  virtual void Exit(NPC* ai);

private:
	/// flee state consructor
	Wander(){}

	Vec3 wanderTarget;

  //copy ctor and assignment should be private
  Wander(const Wander&);
  Wander& operator=(const Wander&);
};

#pragma endregion wander

#endif