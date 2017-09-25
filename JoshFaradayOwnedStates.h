#ifndef JOSHFARADAY_OWNED_STATES_H
#define JOSHFARADAY_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   JoshFaradayOwnedStates.h
//
//  Desc:   All the states that can be assigned to the JoshFaraday class
//
//  Author: Adrien
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class JoshFaraday;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GoSaloonAndDrink : public State<JoshFaraday>
{
private:

	GoSaloonAndDrink() {}

	//copy ctor and assignment should be private
	GoSaloonAndDrink(const GoSaloonAndDrink&);
	GoSaloonAndDrink& operator=(const GoSaloonAndDrink&);


public:

	//this is a singleton
	static GoSaloonAndDrink* Instance();

	virtual void Enter(JoshFaraday* josh);

	virtual void Execute(JoshFaraday* josh);

	virtual void Exit(JoshFaraday* josh);

	virtual bool OnMessage(JoshFaraday* agent, const Telegram& msg); //agent instead of josh

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GoHouseAndSleep : public State<JoshFaraday>
{
private:

	GoHouseAndSleep() {}

	//copy ctor and assignment should be private
	GoHouseAndSleep(const GoHouseAndSleep&);
	GoHouseAndSleep& operator=(const GoHouseAndSleep&);

public:

	//this is a singleton
	static GoHouseAndSleep* Instance();

	virtual void Enter(JoshFaraday* josh);

	virtual void Execute(JoshFaraday* josh);

	virtual void Exit(JoshFaraday* josh);

	virtual bool OnMessage(JoshFaraday* agent, const Telegram& msg);

};

class DrinkWithBob : public State<JoshFaraday>
{
private:

	DrinkWithBob() {}

	//copy ctor and assignment should be private
	DrinkWithBob(const DrinkWithBob&);
	DrinkWithBob& operator=(const DrinkWithBob&);

public:

	//this is a singleton
	static DrinkWithBob* Instance();

	virtual void Enter(JoshFaraday* josh);

	virtual void Execute(JoshFaraday* josh);

	virtual void Exit(JoshFaraday* josh);

	virtual bool OnMessage(JoshFaraday* agent, const Telegram& msg);
};


// HitBob
class HitBob : public State<JoshFaraday>
{
private:

	HitBob() {}

	//copy ctor and assignment should be private
	HitBob(const HitBob&);
	HitBob& operator=(const HitBob&);

public:

	//this is a singleton
	static HitBob* Instance();

	virtual void Enter(JoshFaraday* josh);

	virtual void Execute(JoshFaraday* josh);

	virtual void Exit(JoshFaraday* josh);

	virtual bool OnMessage(JoshFaraday* josh, const Telegram& msg);
};

#endif