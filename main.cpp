#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Barman.h"
#include "JoshFaraday.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create our barman
  Barman* barman = new Barman(ent_Barman);

  //create Josh Faraday
  JoshFaraday* Josh = new JoshFaraday(ent_Josh);
  //initialize its drunk level
  Josh->m_iNotDrunk = 0;

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(barman);
  EntityMgr->RegisterEntity(Josh);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
	barman->Update();
	Josh->Update();
	 
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(2000);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete barman;
  delete Josh;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






