#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#define NUM_TYPE 18
#define NUM_STAT 6
#define NUM_POKE 807

class Pokemon {
private:
    int id;
    std::string name;
    bool is_mine;
    std::vector<int> stats;
    int evolve_from;
    std::vector<int> evolve_to;
    
    std::vector<int> type_id;
    std::vector<std::string> type_name;
    std::vector<int> skill_id;
    std::vector<std::string> skill_name;
    std::vector<std::string> skill_type; // flying, normal
    std::vector<std::string> skill_as; // attack, special

public:
    // rule of three
    Pokemon(bool _is_mine, std::vector<int> init);
    Pokemon& operator=(const Pokemon& poke);
    //~Pokemon(); 

    // Getter function
    int get_id() const;
    std::string get_name() const;
    bool get_is_mine() const;
    std::vector<int> get_stats() const;
    int get_evolve_from() const;
    std::vector<int> get_evolve_to() const;
    std::vector<int> get_type_id() const;
    std::vector<std::string> get_type_name() const;
    std::vector<int> get_skill_id() const;
    std::vector<std::string> get_skill_name() const;
    std::vector<std::string> get_skill_type() const;
    std::vector<std::string> get_skill_as() const;
    
    // Setter function
    void set_is_mine(bool own);
    void set_stats(int _stat_id, int _stat);
    void set_type(std::vector<int> _type_id, std::vector<std::string> _type_name);
    void add_skill(int _skill_id);
    void remove_skill(int index);

    //swap -> for evolution
    void swap_skill_id(std::vector<int> _skill_id);
    void swap_skill_name(std::vector<std::string> _skill_name);
    void swap_skill_type(std::vector<std::string> _skill_type);
    void swap_skill_as(std::vector<std::string> _skill_as);

    void print_poke_info();
};


#endif