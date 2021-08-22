#ifndef BATTLE_H
#define BATTLE_H

#include "pokemon.hpp"
#include "poke_DS.hpp"
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#define NUM_TYPE 18
#define NUM_STAT 6
#define NUM_POKE 807

int compute_damage(Pokemon A, Pokemon B, int skill_id);

void print_efficacy(Pokemon my_poke, Pokemon enemy);

int battle_process(Pokemon my_poke, Pokemon enemy);

Pokemon reward(Pokemon my_poke, Pokemon enemy);

Pokemon battle(Pokemon my_poke);

#endif