#ifndef BARMAN_H
#define BARMAN_H
//------------------------------------------------------------------------
//
//  Name:   Barman.h
//
//  Desc:   A class defining a barman.
//
//  Author: Martin Rohmer
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "BarmanOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

class Barman : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Barman>*  m_pStateMachine;

	location_type          m_Location;

	int                   m_Money;

public:

	Barman(int id) :
		m_Location(saloon),
		BaseGameEntity(id),
		m_Money(0)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Barman>(this);

		m_pStateMachine->SetCurrentState(WaitingForAClient::Instance());
	}

	~Barman() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Barman>* GetFSM()const { return m_pStateMachine; }


	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) {
		m_Location = loc;
	};

	void          OneWhiskeySold() { m_Money += 1;}
	void          TwoWhiskeysSold() { m_Money += 2; }


};

#endif