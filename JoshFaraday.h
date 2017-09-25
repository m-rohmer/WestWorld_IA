#ifndef JOSHFARADAY_H
#define JOSHFARADAY_H

//------------------------------------------------------------------------
//
//  Name: JoshFaraday.h
//
//  Desc:   class to implement Josh Faraday.
//
//  Author: Adrien
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "JoshFaradayOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

//above this value Josh is drunk
const int				NotDrunkLevel = 4;

class JoshFaraday : public BaseGameEntity
{


private:

	//an instance of the state machine class
	StateMachine<JoshFaraday>* m_pStateMachine;


	location_type   m_Location;

public:

	//plus cette valeur est grande plus Josh est bourré
	int                   m_iNotDrunk;

	JoshFaraday(int id) :m_Location(joshhouse),
		m_iNotDrunk(NotDrunkLevel),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<JoshFaraday>(this);

		m_pStateMachine->SetCurrentState(GoHouseAndSleep::Instance());
	}

	~JoshFaraday() { delete m_pStateMachine; }


	///this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<JoshFaraday>* GetFSM()const { return m_pStateMachine; }


	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	//int			GetNotDrunk(){return m_iNotDrunk;}
	//int			GetNotDrunkLevel(){return NotDrunkLevel;}

	bool          NotDrunk()const;

	void          BuyAndDrinkADoubleWhiskey() { m_iNotDrunk += 1; }
	void          SleepAndRest() { m_iNotDrunk -= 2; }

	// Bob paye sa tournée
	void          DrinkAWhiskeyFromBob() { m_iNotDrunk += 1; }

};


#endif