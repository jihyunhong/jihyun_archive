#include "pokemon.hpp"
#include "poke_DS.hpp"
#include <iostream>

Pokemon::Pokemon(bool _is_mine, std::vector<int> init) {
    std::ifstream ifs;
    std::string line;
    std::stringstream ss;

    if (init.size() == 0) {
        exit(1);
    }
    id = init.at(0);
    is_mine = _is_mine;
    evolve_from = -1;

    // LOAD name, evolve_from, evolve_to
    ifs.open("pokeDB/pokemon_species.csv");
    std::getline(ifs, line);
    
    while (!ifs.eof()) {
        std::getline(ifs, line);
        ss << line;
        std::string data;
        std::getline(ss, data, ',');
        
        if (std::stoi(data) == id) {
            std::getline(ss, data, ',');
            name = data;
            std::getline(ss, data, ',');
            if (data != "") {
                evolve_from = std::stoi(data);
            }
            std::ifstream ifs2;
            std::string line2;
            std::stringstream ss2;
            ifs2.open("pokeDB/pokemon_species.csv");
            std::getline(ifs2, line2);
            while (!ifs2.eof()) {
                std::getline(ifs2, line2);
                ss2 << line2;
                std::string data2;
                std::getline(ss2, data2, ',');
                int _id = std::stoi(data2);
                std::getline(ss2, data2, ',');
                std::getline(ss2, data2, ',');
                if (data2 == "") {
                    ss2.clear();
                    ss2.str("");
                    continue;
                }
                else if (std::stoi(data2) == id) {
                    evolve_to.push_back(_id);
                }
                ss2.clear();
                ss2.str("");
            }
            ifs2.close();
            ss.clear();
            ss.str("");
            break;
        }
        ss.str("");
    }
    ifs.close();
    
    // LOAD stats
    ifs.open("pokeDB/pokemon_stats.csv");
    std::getline(ifs, line);
       
    while (!ifs.eof()) {
        std::getline(ifs, line);
        ss << line;
        std::string data;
        std::getline(ss, data, ',');
        
        if (std::stoi(data) == id) {
            std::getline(ss, data, ',');
            std::getline(ss, data, ',');
            stats.push_back(std::stoi(data));
            ss.clear();
            ss.str("");
            for (int i=0; i<5; i++) {
                std::getline(ifs, line);
                ss << line;
                std::getline(ss, data, ',');
                std::getline(ss, data, ',');
                std::getline(ss, data, ',');
                stats.push_back(std::stoi(data));
                ss.clear();
                ss.str("");
            }
            break;
        }
        ss.str("");
    }
    ifs.close();
    
    // LOAD type id
    ifs.open("pokeDB/pokemon_types.csv");
    std::getline(ifs, line);
    
    while (!ifs.eof()) {
        std::getline(ifs, line);
        ss << line;
        std::string data;
        std::getline(ss, data, ',');
        if (std::stoi(data) == id) {
            std::getline(ss, data, ',');
            type_id.push_back(std::stoi(data));
            ss.clear();
            ss.str("");
            std::getline(ifs, line);
            ss << line;
            std::getline(ss, data, ',');
            if (std::stoi(data) == id) {
                std::getline(ss, data, ',');
                type_id.push_back(std::stoi(data));
                ss.clear();
                ss.str("");
                break;
            }
            ss.clear();
            ss.str("");
            break;
        }
        ss.clear();
        ss.str("");
    }
    ifs.close();
    
    // LOAD type name
    
    for (int i=0; i<type_id.size(); i++) {
        ifs.open("pokeDB/types.csv");
        std::getline(ifs, line);
        while (!ifs.eof()) {
            std::getline(ifs, line);
            ss << line;
            std::string data;
            std::getline(ss, data, ',');
            if (type_id.at(i) == std::stoi(data)) {
                std::getline(ss, data, ',');
                // 'ice'는 ' ice'로 받아들이는듯 
                if (data[0] == ' ') {
                    data.erase(0, 1);
                }
                // remove carriage return \r
                for (int i=0; i<data.size(); i++) {
                    if (data[i] == '\r') {
                        data.erase(i, 1);
                        break;
                    }
                }
                type_name.push_back(data);
                ss.clear();
                ss.str("");
                break;
            }
            ss.clear();
            ss.str("");
        }
        ifs.close();
    }
    
    
    // LOAD skill
    if (init.size() > 1) { // 적 포켓몬인데, 학습 스킬이 지정된 경우
        for (int i=1; i<init.size(); i++) {
            add_skill(init.at(i));
        }
    }
    else { // 학습 스킬 미지정
        // 일단 아군이든, 적이든, 자신에게 해당되는 type의 스킬은 배워야함 (1개 or 2개)    
        if (!is_mine) { // 적이면
            // Attack이 우세한지, Special이 우세한지,
            std::string AS;
            if (stats.at(1) > stats.at(3)) {
                AS = "attack";
            }
            else if (stats.at(1) < stats.at(3)) {
                AS = "special";
            }
            else { // attack == special_attack in stat
                int as = rand() % 2;
                if (as == 0) {
                    AS = "attack";
                }
                else {
                    AS = "special";
                }
            }
            
            std::vector<int> dummy;
            int count = 0;
            for (int i=0; i<type_name.size(); i++) {
                
                ifs.open("pokeDB/skill_list.txt");

                while(!ifs.eof()) {
                    count += 1;
                    std::getline(ifs, line);
                    ss << line;
                    std::string data;
                    std::getline(ss, data, '.');
                    int _skill_id = std::stoi(data);

                    std::getline(ss, data, ':');
                    data.erase(0, 1);
                    std::string _skill_name = data;

                    std::getline(ss, data, ',');
                    data.erase(0, 1);
                    std::string _skill_type = data;

                    std::getline(ss, data);
                    data.erase(0, 1);
                    // remove carriage return \r
                    for (int i=0; i<data.size(); i++) {
                        if (data[i] == '\r') {
                            data.erase(i, 1);
                            break;
                        }
                    }
                    std::string _skill_as = data;
                    
                    if (_skill_type == type_name.at(i) && _skill_as == AS) {
                        add_skill(_skill_id);
                        dummy.push_back(_skill_id);
                    }

                    ss.clear();
                    ss.str("");
                }
                ifs.close();
            }
            
            while (true) {
                int pick = rand() % (count / type_name.size()) + 1;
                int token = 0;
                for (int i=0; i<dummy.size(); i++) {
                    if (pick == dummy.at(i)) {
                        token = 1;
                    }
                }
                if (token != 1) {
                    add_skill(pick);
                    dummy.push_back(pick);
                }
                if (skill_id.size() >= 4) {
                    break;
                }
            }
        }
        else { //아군이면,
            std::string AS;
            int as = rand() % 2;
            if (as == 0) {
                AS = "attack";
            }
            else {
                AS = "special";
            }
            
            for (int i=0; i<type_name.size(); i++) {
                ifs.open("pokeDB/skill_list.txt");
                while(!ifs.eof()) {
                    std::getline(ifs, line);
                    ss << line;
                    std::string data;
                    std::getline(ss, data, '.');
                    int _skill_id = std::stoi(data);
                    
                    std::getline(ss, data, ':');
                    data.erase(0, 1);
                    std::string _skill_name = data;
                    
                    std::getline(ss, data, ',');
                    data.erase(0, 1);
                    std::string _skill_type = data;
                    
                    std::getline(ss, data);
                    data.erase(0, 1);
                    // remove carriage return \r
                    for (int i=0; i<data.size(); i++) {
                        if (data[i] == '\r') {
                            data.erase(i, 1);
                            break;
                        }
                    }
                    std::string _skill_as = data;

                    if (_skill_type == type_name.at(i) && _skill_as == AS) {
                        add_skill(_skill_id);
                    }
                    ss.clear();
                    ss.str("");
                }
                ifs.close();
            }
        }
    }
}

Pokemon& Pokemon::operator=(const Pokemon& poke) {
    id = poke.id;
    name = poke.name;
    is_mine = poke.is_mine;
    stats = poke.stats;
    evolve_from = poke.evolve_from;
    evolve_to = poke.evolve_to;
    type_id = poke.type_id;
    type_name = poke.type_name;
    skill_id = poke.skill_id;
    skill_name = poke.skill_name;
    skill_type = poke.skill_type;
    skill_as = poke.skill_as;
    return *this;
}

int Pokemon::get_id() const {
    return id;
}

std::string Pokemon::get_name() const {
    return name;
}

bool Pokemon::get_is_mine() const {
    return is_mine;
}

std::vector<int> Pokemon::get_stats() const {
    return stats;
}

int Pokemon::get_evolve_from() const {
    return evolve_from;
}

std::vector<int> Pokemon::get_evolve_to() const {
    return evolve_to;
}

std::vector<int> Pokemon::get_type_id() const {
    return type_id;
}

std::vector<std::string> Pokemon::get_type_name() const {
    return type_name;
}

std::vector<int> Pokemon::get_skill_id() const {
    return skill_id;
}

std::vector<std::string> Pokemon::get_skill_name() const {
    return skill_name;
}

std::vector<std::string> Pokemon::get_skill_type() const {
    return skill_type;
}

std::vector<std::string> Pokemon::get_skill_as() const {
    return skill_as;
}

void Pokemon::set_is_mine(bool own) {
    is_mine = own;
}

void Pokemon::set_stats(int _stat_id, int _stat) {
    if (_stat_id < 0 || _stat_id > 5) {
        return;
    }
    stats.at(_stat_id) = _stat;
}

void Pokemon::set_type(std::vector<int> _type_id, std::vector<std::string> _type_name) {
    type_id.clear();
    type_name.clear();
    for (int i=0; i<_type_id.size(); i++) {
        type_id.push_back(_type_id.at(i));
        type_name.push_back(_type_name.at(i));
    }
}
void Pokemon::swap_skill_id(std::vector<int> _skill_id){
    skill_id.swap(_skill_id);
}

void Pokemon::swap_skill_name(std::vector<std::string> _skill_name){
    skill_name.swap(_skill_name);
}

void Pokemon::swap_skill_type(std::vector<std::string> _skill_type){
    skill_type.swap(_skill_type);
}

void Pokemon::swap_skill_as(std::vector<std::string> _skill_as){
    skill_as.swap(_skill_as);
}



void Pokemon::add_skill(int _skill_id) {
    
    std::string _skill_name;
    std::string _skill_type;
    std::string _skill_as;

    std::ifstream ifs;
    std::string line;
    std::stringstream ss;
    
    ifs.open("pokeDB/skill_list.txt");
    while(!ifs.eof()) {
        std::getline(ifs, line);
        ss << line;
        std::string data;
        std::getline(ss, data, '.');
        if (std::stoi(data) != _skill_id) {
            ss.clear();
            ss.str("");
            continue;
        }
        else {
            std::getline(ss, data, ':');
            data.erase(0, 1);
            _skill_name = data;
            std::getline(ss, data, ',');
            data.erase(0, 1);
            _skill_type = data;
            std::getline(ss, data, ' ');
            data.erase(0, 1);
            // remove carriage return \r
            for (int i=0; i<data.size(); i++) {
                if (data[i] == '\r') {
                    data.erase(i, 1);
                    break;
                }
            }
            _skill_as = data;
            break;
        }
    }
    ifs.close();
    
    skill_id.push_back(_skill_id);
    skill_name.push_back(_skill_name);
    skill_type.push_back(_skill_type);
    skill_as.push_back(_skill_as);
}

void Pokemon::remove_skill(int index) {
    skill_id.erase(skill_id.begin() + index);
    skill_name.erase(skill_name.begin() + index);
    skill_type.erase(skill_type.begin() + index);
    skill_as.erase(skill_as.begin() + index);
}


void Pokemon::print_poke_info() {
    std::ifstream ifs;
    std::string line;
    std::stringstream ss;
    
    if (is_mine) {
        std::cout << "your pokemon info" << std::endl;
        std::cout << "pokemon_id: " << id << ", pokemon_name: " << name << std::endl;
        if (evolve_from != -1) {
            ifs.open("pokeDB/pokemon_species.csv");
            std::getline(ifs, line);
            while (!ifs.eof()) {
                std::getline(ifs, line);
                ss << line;
                std::string data;
                std::getline(ss, data, ',');
                if (std::stoi(data) == evolve_from) {
                    std::getline(ss, data, ',');
                    std::cout << "evolved from " << data << std::endl;
                    ss.clear();
                    ss.str("");
                    break;
                }
                ss.clear();
                ss.str("");
            }
            ifs.close();
        }
        if (evolve_to.size() > 0) {
            std::cout << "candidates to be evolved: ";
            for (int i=0; i<evolve_to.size(); i++) {
                ifs.open("pokeDB/pokemon_species.csv");
                std::getline(ifs, line);
                while (!ifs.eof()) {
                    std::getline(ifs, line);
                    ss << line;
                    std::string data;
                    std::getline(ss, data, ',');
                    if (evolve_to.at(i) == std::stoi(data)) {
                        std::getline(ss, data, ',');
                        std::cout << data << " ";
                        ss.clear();
                        ss.str("");
                        break;
                    }
                    ss.clear();
                    ss.str("");
                }
                ifs.close();
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "wild pokemon " << name << " appeared" <<std::endl;
        std::cout << "enemy pokemon's information" << std::endl;
        std::cout << "pokemon_id: " << id << ", pokemon_name: " << name << std::endl;
    }
    
    // stat 출력
    std::cout << "stat: ";
    ifs.open("pokeDB/stats.csv");
    std::getline(ifs, line);
    std::getline(ifs, line);
    while(!ifs.eof()) {
        ss << line;
        std::string data;
        std::getline(ss, data, ',');
        int index = std::stoi(data) - 1;
        std::getline(ss, data, ',');
        // remove carriage return \r
        for (int i=0; i<data.size(); i++) {
            if (data[i] == '\r') {
                data.erase(i, 1);
                break;
            }
        }
        std::cout << data << " " << stats.at(index) << " ";
        ss.clear();
        ss.str("");
        std::getline(ifs, line);
    }
    ifs.close();
    std::cout << std::endl;
    
    // type 출력
    std::cout << "type: ";
    for (int i=0; i<type_name.size(); i++) {
        std::cout << type_name.at(i) << " ";
    }
    std::cout << std::endl;
    
    // skill 출력
    std::cout << "skill: " << skill_name.at(0);
    for (int i=1; i<skill_name.size(); i++) {
        std::cout << "/" << skill_name.at(i);
    }
    std::cout << std::endl;
}
