#include "BarmanOwnedStates.h"
#include "fsm/State.h"
#include "Barman.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for WaitingForAClient
WaitingForAClient* WaitingForAClient::Instance()
{
	static WaitingForAClient instance;

	return &instance;
}

void WaitingForAClient::Enter(Barman * barman)
{

}


void WaitingForAClient::Execute(Barman* pBarman)
{
	cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": " 
		<< "cleaning glasses";
}


void WaitingForAClient::Exit(Barman* pBarman)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": "
		<< "What can I do for ya?";
}


bool WaitingForAClient::OnMessage(Barman* pBarman, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
		case Msg_WannaDrinkWhiskey:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pBarman->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pBarman->GetFSM()->ChangeState(ServingOneWhiskey::Instance());
			return true;
		}
		case Msg_OrderTwoWhiskeys:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pBarman->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pBarman->GetFSM()->ChangeState(ServingTwoWhiskeys::Instance());
			return true;
		}
		case Msg_FightBeginning:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pBarman->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pBarman->GetFSM()->ChangeState(angryBarman::Instance());
			return true;
		}

	}//end switch

	return false;
}

//------------------------------------------------------------------------methods for ServingOneWhiskey

ServingOneWhiskey* ServingOneWhiskey::Instance()
{
	static ServingOneWhiskey instance;

	return &instance;
}

void ServingOneWhiskey::Enter(Barman * pBarman)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": "
		<< "Here for you sir";
}


void ServingOneWhiskey::Execute(Barman* pBarman)
{
	pBarman->OneWhiskeySold();
	pBarman->GetFSM()->ChangeState(WaitingForAClient::Instance());
}


void ServingOneWhiskey::Exit(Barman* pBarman)
{

}


bool ServingOneWhiskey::OnMessage(Barman* pBarman, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for ServingTwoWhiskeys

ServingTwoWhiskeys* ServingTwoWhiskeys::Instance()
{
	static ServingTwoWhiskeys instance;

	return &instance;
}

void ServingTwoWhiskeys::Enter(Barman * pBarman)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": "
		<< "Some good whiskeys for these big guys";
}


void ServingTwoWhiskeys::Execute(Barman* pBarman)
{
	pBarman->TwoWhiskeysSold();
	pBarman->GetFSM()->ChangeState(WaitingForAClient::Instance());
}


void ServingTwoWhiskeys::Exit(Barman* pBarman)
{

}


bool ServingTwoWhiskeys::OnMessage(Barman* pBarman, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for angryBarman

angryBarman* angryBarman::Instance()
{
	static angryBarman instance;

	return &instance;
}

void angryBarman::Enter(Barman * pBarman)
{
	Sleep(500);
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": "
		<< "Imma grab ma shotgun! Go out, ya b*stards!";
}


void angryBarman::Execute(Barman* pBarman)
{
	//Ask the barman for help
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pBarman->ID(),        //ID of sender
		ent_Josh,            //ID of recipient
		Msg_GoOut,   //the message
		NO_ADDITIONAL_INFO);

	pBarman->GetFSM()->ChangeState(WaitingForAClient::Instance());
}


void angryBarman::Exit(Barman* pBarman)
{

}


bool angryBarman::OnMessage(Barman* pBarman, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}
