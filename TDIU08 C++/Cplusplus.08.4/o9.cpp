#include "hero_handling.h"
#include "register_handling.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;


vector<int> load_array_interests() 
{                                  
  vector<int> numb{};
  stringstream ss;
  int integer{};
  string s;
  
  getline(cin,s);
  ss.str(s);
  
  while(ss >> integer)
    {
      if((integer < 16) and (integer > 0))
	{
	  numb.push_back(integer);
	}
    }
  return numb;
}

//------------------------------------------------//
void hero_register(Register_Type       & heroes,
		   string        const & file_name) 
{
  Hero_Type hero;
  
  while (true)
    {
      cout << "Enter hero information:" << endl;
      
      if (not new_hero(heroes, file_name)) 
	{
	  cout << "Hero already in register. ";
	  cin.ignore(1000,'\n');
    }
      else
	{
      break;
	} 
    }
  cout << "The hero was added to the register on file " << file_name << endl;
}
//------------------------------------------------//
void hero_finder (Register_Type & heroes)
{
  Register_Type match_heroes {};
  vector<int> numb{};
  
  cin.ignore(1000,'\n'); 
  cout << "Enter your interests (at least one between 1 and 15): ";
  
  while (true)
    {
      numb = load_array_interests();
      
      if (numb.size() > 0)
	{
	  break;
	}
    }
  
  match_heroes = search_heroes(heroes, numb);
  cout << "There are " << match_heroes.size() << " matching heroes." << endl;
  cout << "Hero name  Birth year  Weight  Hair color  Interests"<< endl;
  cout << "===================================================="<< endl;
  
  print_heroes(cout, match_heroes);
  
}
//------------------------------------------------//
void print_menu()
{
  cout << "1) Add new hero to register file" << endl
       << "2) Find matching heroes" << endl
       << "3) Quit program" << endl;
}

void menu_selection (int & selection)
{
  print_menu();
  
  while(true)
    {
      cout << "Select: ";
      cin >> selection;
      
      if ((selection > 0) and (selection < 4))
	{
	  break;		   
	}
    }
}
//------------------------------------------------//
void menu (Register_Type       & heroes,
	   string        const & file_name)
{
  int selection;
  cout << "Welcome to Hero Matchmaker 3000!" << endl;
  while (true)
    {
      menu_selection(selection);
      
      if (selection == 1)
	{
	  hero_register(heroes, file_name);
	}
      
      else if (selection == 2)
	{
	  hero_finder(heroes);
	}
      
      else if (selection == 3)
	{
      break;
	}
    }
  
  cout << "Terminating Hero Matchmaker 3000!";
}
//-------------------MAIN-------------------------//
int main(int argc, char*argv[])
{
  ifstream hero_file; 
  Register_Type heroes;
  string file_name{};
  
  if (argc < 2 or argc > 2)
    {
      cout << "Incorrect number of arguments!" << endl
	   << "Usage: " << argv[0] << " REGISTERFILE";
    }
  else
    {
      file_name = argv[1];
      hero_file.open(argv[1]);
      heroes = read_file(hero_file); 
      hero_file.close(); 
      
      menu(heroes, file_name); 
    }
  return 0;
}
