#ifndef BARMAN_OWNED_STATES_H
#define BARMAN_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   BarmanOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Barman class.
//          Note that a global state has not been implemented.
//
//  Author: Martin Rohmer
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Barman;
struct Telegram;




//------------------------------------------------------------------------

class WaitingForAClient : public State<Barman>
{
private:

	WaitingForAClient() {}

	//copy ctor and assignment should be private
	WaitingForAClient(const WaitingForAClient&);
	WaitingForAClient& operator=(const WaitingForAClient&);

public:

	//this is a singleton
	static WaitingForAClient* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};


//------------------------------------------------------------------------
class ServingOneWhiskey : public State<Barman>
{
private:

	ServingOneWhiskey() {}

	//copy ctor and assignment should be private
	ServingOneWhiskey(const ServingOneWhiskey&);
	ServingOneWhiskey& operator=(const ServingOneWhiskey&);

public:

	//this is a singleton
	static ServingOneWhiskey* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
class ServingTwoWhiskeys : public State<Barman>
{
private:

	ServingTwoWhiskeys() {}

	//copy ctor and assignment should be private
	ServingTwoWhiskeys(const ServingTwoWhiskeys&);
	ServingTwoWhiskeys& operator=(const ServingTwoWhiskeys&);

public:

	//this is a singleton
	static ServingTwoWhiskeys* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};

//------------------------------------------------------------------------

class angryBarman : public State<Barman>
{
private:

	angryBarman() {}

	//copy ctor and assignment should be private
	angryBarman(const angryBarman&);
	angryBarman& operator=(const angryBarman&);

public:

	//this is a singleton
	static angryBarman* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};

#endif