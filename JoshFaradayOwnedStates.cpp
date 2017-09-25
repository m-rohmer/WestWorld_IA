#include "JoshFaradayOwnedStates.h"
#include "fsm/State.h"
#include "JoshFaraday.h"
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


//------------------------------------------------------------------------GoSaloonAndDrink

GoSaloonAndDrink* GoSaloonAndDrink::Instance()
{
	static GoSaloonAndDrink instance;

	return &instance;
}

void GoSaloonAndDrink::Enter(JoshFaraday* pJosh)
{
	if (pJosh->Location() != saloon)
	{
		pJosh->ChangeLocation(saloon);

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Need a whiskey ! Walking to the saloon";


		//let Bob know Josh already here
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pJosh->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_HiDeJoshQuiEntre,   //the message
			NO_ADDITIONAL_INFO);

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Hi motherfuc*er";
	}
}

void GoSaloonAndDrink::Execute(JoshFaraday* pJosh)
{
	pJosh->BuyAndDrinkADoubleWhiskey();

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pJosh->ID(),        //ID of sender
		ent_Barman,            //ID of recipient
		Msg_WannaDrinkWhiskey,   //the message
		NO_ADDITIONAL_INFO);

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	if (!(pJosh->NotDrunk()))
	{
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Guess it was the last one for today...";
		pJosh->GetFSM()->ChangeState(GoHouseAndSleep::Instance());
	}
	else
	{
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "I finish my drink! One more!";
	}
}


void GoSaloonAndDrink::Exit(JoshFaraday* pJosh)
{
	if (!(pJosh->NotDrunk()))
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Leaving the saloon, imma so damn drunk...jfepheb? ";
	}
}


bool GoSaloonAndDrink::OnMessage(JoshFaraday* pJosh, const Telegram& msg)
{

	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
		/// Cas n°1 : Bob entre dans le bar après Josh
	case Msg_HiDeBobQuiEntre:

		cout << "\nMessage handled by " << GetNameOfEntity(pJosh->ID())
			<< " at time: " << Clock->GetCurrentTime();

		Sleep(500);
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": Hi Bob! Imma here!";

		//let Bob know Josh already here
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pJosh->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_JoshHiRetour,   //the message
			NO_ADDITIONAL_INFO);

		pJosh->GetFSM()->ChangeState(DrinkWithBob::Instance());

		return true;

		/// Cas n°2 : Bob est déjà dans le bar et à répondu à Josh
	case Msg_BobHiRetour:

		cout << "\nMessage handled by " << GetNameOfEntity(pJosh->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": Comm'in right now!";

		pJosh->GetFSM()->ChangeState(DrinkWithBob::Instance());

		return true;

	}//end switch

	 //send msg to global message handler
	return false;
}


//------------------------------------------------------------------------methods for GoHouseAndSleep

GoHouseAndSleep* GoHouseAndSleep::Instance()
{
	static GoHouseAndSleep instance;

	return &instance;
}

void GoHouseAndSleep::Enter(JoshFaraday* pJosh)
{
	if (pJosh->Location() != joshhouse)
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Walkin' home... my house so far...";

		pJosh->ChangeLocation(joshhouse);
	}
}

void GoHouseAndSleep::Execute(JoshFaraday* pJosh)
{
	if (pJosh->m_iNotDrunk > 0) {
		//if drunk, sleep still totaly not drunk
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "ZZZZZZZZZZZZZzzzzzz... ";

		pJosh->SleepAndRest();
		pJosh->GetFSM()->ChangeState(GoHouseAndSleep::Instance());
	}
	else {
		//else go to the saloon
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": "
			<< "Sober now, let's go get some whiskey!";

		pJosh->GetFSM()->ChangeState(GoSaloonAndDrink::Instance());
	}
}

bool GoHouseAndSleep::OnMessage(JoshFaraday* pJosh, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

void GoHouseAndSleep::Exit(JoshFaraday* pJosh)
{
}


//------------------------------------------------------------------------methods for DrinkWithBob

DrinkWithBob* DrinkWithBob::Instance()
{
	static DrinkWithBob instance;

	return &instance;
}

void DrinkWithBob::Enter(JoshFaraday* pJosh)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Sleep(500);
	cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Imma alright!";
}

void DrinkWithBob::Execute(JoshFaraday* pJosh)
{
	pJosh->DrinkAWhiskeyFromBob();

	cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "It's good to see ya!";

	if (!(pJosh->NotDrunk()))
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pJosh->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_JoshVeutTaperBob,   //the message
			NO_ADDITIONAL_INFO);

		SetTextColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);

		Sleep(500);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Bob Imma gonna kill you!";

		pJosh->GetFSM()->ChangeState(HitBob::Instance());
	}

}

void DrinkWithBob::Exit(JoshFaraday* pJosh)
{
	//cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "A whiskey please";
}

bool DrinkWithBob::OnMessage(JoshFaraday* pJosh, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
		// Si Bob se barre avant que Josh soit bourré
	case Msg_ByeDeBob:

		cout << "\nMessage handled by " << GetNameOfEntity(pJosh->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pJosh->ID())
			<< ": Good bye bro' ! I stay";

		pJosh->GetFSM()->ChangeState(GoSaloonAndDrink::Instance());
		return true;

	}//end switch

	 //send msg to global message handler
	return false;
}


//------------------------------------------------------------------------methods for HitBob

HitBob* HitBob::Instance()
{
	static HitBob instance;

	return &instance;
}

void HitBob::Enter(JoshFaraday* pJosh)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "You can run but you can't Hide BEATCH !";
}

void HitBob::Execute(JoshFaraday* pJosh)
{

	Sleep(2000);

	cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "Screw you Bob ! Imma gonna leave !";

	pJosh->GetFSM()->ChangeState(GoHouseAndSleep::Instance());


}

void HitBob::Exit(JoshFaraday* pJosh)
{
	//cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": " << "A whiskey please";
	//let Bob know Josh is leaving
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pJosh->ID(),        //ID of sender
		ent_Miner_Bob,            //ID of recipient
		Msg_JoshAbandonneRechercheBob,   //the message
		NO_ADDITIONAL_INFO);
}

bool HitBob::OnMessage(JoshFaraday* pJosh, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_GoOut:

		cout << "\nMessage handled by " << GetNameOfEntity(pJosh->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pJosh->ID()) << ": Im fucked up...";


		pJosh->GetFSM()->ChangeState(GoHouseAndSleep::Instance());

		return true;

	}//end switch

	return false;
}


