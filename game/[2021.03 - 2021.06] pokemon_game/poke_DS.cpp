#include "poke_DS.hpp"
#include <iostream>
#include <vector>

std::vector<int> poke_generator(){
    //readf.open("pokeDB/pokemon_stats.csv");
    //return (rand()%NUM_POKE)+1;
    std::vector<int> poke_information;
    std::string buf_string;
    std::getline(next_poke_f, buf_string);

    std::istringstream ss(buf_string);
    std::string token;
    std::getline(ss, token, ',');

    int selection;
    if(is_number(token)){
        selection=std::stoi(token);
    }
    else{
        selection=0;
    }
    if(selection==0){
        poke_information.push_back((rand()%NUM_POKE)+1);
    }
    else{
        poke_information.push_back(selection);
        while(std::getline(ss, token, ',')){
            poke_information.push_back(std::stoi(token));
        }
    }
    return poke_information;
}
void initializer(){
    srand(time(0));
    next_poke_f.open("pokeDB/next_pokemon.txt");
}
void terminator(){
    next_poke_f.close();
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

