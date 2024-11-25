#include "hero_handling.h"
#include "register_handling.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool read_hero(ifstream  & hero_file,
	       Hero_Type & hero)
{
  int intressen{};
  string s {};
  stringstream ss;
  
  if(not (hero_file >> hero.name)) //finns det inga hjältar kvar = returnera false(klar)
    {
      return false;
    }
  else
    { 
      hero_file >> hero.birthdate;   //hero.name laddas in automatiskt mha ovanstående ifsats
      hero_file >> hero.weight;
      hero_file >> hero.hair;
      
      getline(hero_file, s);
      ss.str(s);
    
    while (ss >> intressen)
      {
	hero.interests.push_back(intressen);
      }
    
    return true;                       //om hjältar kvar = läs in hero_file som ovan och returnera true
    }
}
