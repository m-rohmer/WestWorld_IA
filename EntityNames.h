#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa,

  ent_Barman,

  ent_Josh
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa";
  
  case ent_Barman:
	  
	  return "Barman";

  case ent_Josh:

	  return "Josh Faraday";

  default:

    return "UNKNOWN!";
  }
}

#endif