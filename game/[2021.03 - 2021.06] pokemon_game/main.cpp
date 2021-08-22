#include <iostream>
#include "poke_DS.hpp"
#include "pokemon.hpp"
#include "battle.hpp"
#include "configure.hpp"
#include <cstdlib>
#include <ctime>

std::ifstream next_poke_f;
int main(){
    initializer();
    //you can implement anything at here
    
    // Select your pokemon
    std::string choice;
    std::cout << "choose your pokemon among 1. bulbasaur 2. charmander 3. squirtle\nyour choice: ";
    std::cin >> choice;
    while (!is_number(choice) || std::stoi(choice) < 1 || std::stoi(choice) > 3) {
        std::cout << "please insert appropriate number\nyour choice: ";
        std::cin >> choice;
    }

    int id;
    switch (std::stoi(choice)) {
        case 1:
            id = 1;
            break;
        case 2:
            id = 4;
            break;
        case 3:
            id = 7;
            break;
        default:
            exit(1);
    }

    // Print your poke info
    std::vector<int> init;
    init.push_back(id);
    Pokemon my_poke(true, init);
    std::cout << std::endl;
    my_poke.print_poke_info();

    // Main game
    choice = "0";
    while (std::stoi(choice) != 3) {
        std::cout << "\nWhat do you want to do?\n1. battle 2. change your pokemon's stat 3. exit\nyour choice: ";
        std::cin >> choice;
        while (!is_number(choice) || std::stoi(choice) < 1 || std::stoi(choice) > 3) {
            std::cout << "please insert appropriate number\nyour choice: ";
            std::cin >> choice;
        }
        std::cout << std::endl;

        if (std::stoi(choice) == 1) {
            // battle
            my_poke = battle(my_poke);
        }
        else if (std::stoi(choice) == 2) {
            // configure
            my_poke = configure(my_poke);
        }
    }
    terminator();
    return 0;
}