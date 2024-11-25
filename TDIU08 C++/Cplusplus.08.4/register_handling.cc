#include "register_handling.h"
#include "hero_handling.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

/////////////////////////////////////////////////////
bool operator<(Hero_Type const & lhs,
	       Hero_Type const & rhs)
{
  if (lhs.name < rhs.name)
    {
    return true;
  }
  else
    {
    return false;
  }
}

/////////////////////////////////////////////////////
void sorting(Register_Type & heroes)
{
  for (Hero_Type & hero : heroes)
    {
    sort(begin(hero.interests), end(hero.interests));
  }
  sort(begin(heroes), end(heroes));
  
}

///////////////////////////////////////////////////////
void print_heroes (ostream             & write_or_cout,
		   Register_Type const & Heroes) 
{
  write_or_cout << fixed << setprecision(2);
   
   for(int i{}; i <  static_cast<int>(Heroes.size()); i++)
    {
    write_or_cout << setw(11) << left << Heroes.at(i).name;
    write_or_cout << setw(12) << Heroes.at(i).birthdate;
    write_or_cout << setw(8) << Heroes.at(i).weight;
    write_or_cout << setw (12) << Heroes.at(i).hair;
    
    for(int k{}; k < static_cast<int>(Heroes.at(i).interests.size()); k++)
    {
      write_or_cout << setw(3) << right << Heroes.at(i).interests.at(k);
    }    
    
    write_or_cout << endl;
    
  }
}

///////////////////////////////////////////////////
void write_hero(Register_Type       & Heroes,
		string        const & file_name)
{
  ofstream hero_file(file_name, ios::out);
  
  print_heroes(hero_file, Heroes); 
  hero_file.close(); 
}

///////////////////////////////////////////////////
bool new_hero(Register_Type  & Heroes,
	      string   const & file_name)
{
  Hero_Type tmp;
  stringstream ss;
  string s{};
  int intressen {};
  
  cin >> tmp.name;
  for(int i{}; i < static_cast<int>(Heroes.size()); i++)
    {
    if (Heroes.at(i).name == tmp.name)
      {
      return false;
    }
  }
  cin >> tmp.birthdate;
  cin >> tmp.weight;
  cin >> tmp.hair;
  
  getline(cin, s);
  ss.str(s);
  
  while (ss >> intressen)
    {
    tmp.interests.push_back(intressen);
  }

  Heroes.push_back(tmp); 
  sorting(Heroes); 
  write_hero(Heroes, file_name);
  
  return true;
}

///////////////////////////////////////////////////////////////////

Register_Type read_file(ifstream & hero_file)
{
  Hero_Type hero{};
  Register_Type heroes;
  
  while (read_hero(hero_file, hero)) 
    {
    heroes.push_back(hero);
    hero.interests.clear(); 
  }
  
  return heroes;
}

////////////////////////////////////////////////////////////////////////////
bool hero_already_in_registry(Register_Type const & match_heroes,
			      Hero_Type     const & hero) 
{
  for(int i{}; i < static_cast<int>(match_heroes.size()); i++)
    {
      if (match_heroes.at(i).name == hero.name)
	{
	  return true;
	}
    }

return false;
}

///////////////////////////////////////////////////////////////////////
Register_Type search_heroes(Register_Type   const & heroes,
			    vector<int> const & numb)
{
  Register_Type match_heroes{};
  Hero_Type hero{};
  
  for (int i{}; i <static_cast<int>(numb.size()); i++)
    {
      for (int j{}; j < static_cast<int>(heroes.size()); j++)
	{
	  for (int k{}; k < static_cast<int>(heroes.at(j).interests.size()); k++)
	    {
	      if (numb.at(i) == heroes.at(j).interests.at(k))
		{
		  if (not hero_already_in_registry(match_heroes, heroes.at(j)))
		    {
		      hero = heroes.at(j);
		      match_heroes.push_back(hero);	   
		    }
		}
	    }
	}
    }
  sorting(match_heroes); 
  return match_heroes;
}
