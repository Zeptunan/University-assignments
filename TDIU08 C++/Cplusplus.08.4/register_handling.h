#ifndef REGISTER_HANDLING_H
#define REGISTER_HANDLING_H

#include "hero_handling.h"
#include <vector>
#include <string>

using Register_Type = std::vector<Hero_Type>;

bool new_hero(Register_Type     & Heroes,
	      std::string const & file_name);

Register_Type read_file(std::ifstream & hero_file);

Register_Type search_heroes(Register_Type   const & heroes,
			    std::vector<int> const & numb);

void print_heroes (std::ostream & write_or_cout,
		   Register_Type const & match_heroes);

#endif //REGISTER_HANDLING_H
