#ifndef HERO_HANDLING_H
#define HERO_HANDLING_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Hero_Type
{
  std::string name{};
  int birthdate{};
  double weight{};
  std::string hair{};
  std::vector <int> interests{};
};

bool read_hero(ifstream  & hero_file,
	       Hero_Type & hero);

#endif //HERO_HANDLING_H
