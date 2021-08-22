#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "pokemon.hpp"
#include "poke_DS.hpp"
#include "battle.hpp"
#include "configure.hpp"
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#define NUM_TYPE 18
#define NUM_STAT 6
#define NUM_POKE 807

void show_pokeDB();
void show_my_poke_stat(Pokemon my_poke);
Pokemon change_skill(Pokemon my_poke);
Pokemon configure(Pokemon my_poke);

#endif