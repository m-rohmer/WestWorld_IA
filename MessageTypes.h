#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_WannaDrinkWhiskey,
  Msg_OrderTwoWhiskeys,
  Msg_GoOut,
  Msg_FightBeginning,
  Msg_HiDeJoshQuiEntre,
  Msg_HiDeBobQuiEntre,
  Msg_JoshHiRetour,
  Msg_BobHiRetour,
  Msg_ByeDeBob,
  Msg_JoshVeutTaperBob,
  Msg_BobSeCache,
  Msg_JoshAbandonneRechercheBob
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_WannaDrinkWhiskey:

	  return "WannaDrinkWhiskey";
  
  case Msg_OrderTwoWhiskeys:

	  return "OrderTwoWhiskeys";

  case Msg_GoOut:

	  return "GoOut";

  case Msg_FightBeginning:

	  return "FightBeginning";

  case Msg_HiDeJoshQuiEntre:

	  return "HiDeJoshQuiEntre";

  case Msg_HiDeBobQuiEntre:

	  return "HiDeBobQuiEntre";

  case Msg_JoshHiRetour:

	  return "JoshHiRetour";

  case Msg_BobHiRetour:

	  return "BobHiRetour";

  case Msg_ByeDeBob:

	  return "ByeDeBob";

  case Msg_JoshVeutTaperBob:

	  return "JoshVeutTaperBob";

  case Msg_BobSeCache:

	  return "BobSeCache";

  case Msg_JoshAbandonneRechercheBob:

	  return "JoshAbandonneRechercheBob";


  default:

    return "Not recognized!";
  }
}

#endif