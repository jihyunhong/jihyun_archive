#include "configure.hpp"
#include <iostream>

void show_pokeDB(){
    std::ifstream ifs;
    std::string line;
    std::stringstream ss;
    std::string poke_id;
    std::cout << "what pokemon do you want to see? ";
    std::cin >> poke_id;
    while (!is_number(poke_id) || std::stoi(poke_id) < 1 || std::stoi(poke_id) > NUM_POKE) {
        std::cout << "please insert appropriate number\n\n";
        return;
    }
    std::vector<int> init;
    init.push_back(std::stoi(poke_id));
    Pokemon poke(false, init);
    
    std::cout << "pokemon_id: " << poke.get_id() << ", pokemon_name: " << poke.get_name() << std::endl;
    if (poke.get_evolve_from() != -1) {
        ifs.open("pokeDB/pokemon_species.csv");
        std::getline(ifs, line);
        while (!ifs.eof()) {
            std::getline(ifs, line);
            ss << line;
            std::string data;
            std::getline(ss, data, ',');
            if (std::stoi(data) == poke.get_evolve_from()) {
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
    if (poke.get_evolve_to().size() > 0) {
        std::cout << "candidates to be evolved: ";
        for (int i=0; i<poke.get_evolve_to().size(); i++) {
            ifs.open("pokeDB/pokemon_species.csv");
            std::getline(ifs, line);
            while (!ifs.eof()) {
                std::getline(ifs, line);
                ss << line;
                std::string data;
                std::getline(ss, data, ',');
                if (poke.get_evolve_to().at(i) == std::stoi(data)) {
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
        std::cout << data << " " << poke.get_stats().at(index) << " ";
        ss.clear();
        ss.str("");
        std::getline(ifs, line);
    }
    ifs.close();
    std::cout << std::endl;
    
    // type 출력
    std::cout << "type: ";
    for (int i=0; i<poke.get_type_name().size(); i++) {
        std::cout << poke.get_type_name().at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void show_my_poke_stat(Pokemon my_poke){
    std::ifstream ifs;
    std::string line;
    std::stringstream ss;
    std::cout << "pokemon_id: " << my_poke.get_id() << ", pokemon_name: " << my_poke.get_name() << std::endl;
    if (my_poke.get_evolve_from() != -1) {
        ifs.open("pokeDB/pokemon_species.csv");
        std::getline(ifs, line);
        while (!ifs.eof()) {
            std::getline(ifs, line);
            ss << line;
            std::string data;
            std::getline(ss, data, ',');
            if (std::stoi(data) == my_poke.get_evolve_from()) {
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
    if (my_poke.get_evolve_to().size() > 0) {
        std::cout << "candidates to be evolved: ";
        for (int i=0; i<my_poke.get_evolve_to().size(); i++) {
            ifs.open("pokeDB/pokemon_species.csv");
            std::getline(ifs, line);
            while (!ifs.eof()) {
                std::getline(ifs, line);
                ss << line;
                std::string data;
                std::getline(ss, data, ',');
                if (my_poke.get_evolve_to().at(i) == std::stoi(data)) {
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
        std::cout << data << " " << my_poke.get_stats().at(index) << " ";
        ss.clear();
        ss.str("");
        std::getline(ifs, line);
    }
    ifs.close();
    std::cout << std::endl;
    
    // type 출력
    std::cout << "type: ";
    for (int i=0; i<my_poke.get_type_name().size(); i++) {
        std::cout << my_poke.get_type_name().at(i) << " ";
    }
    std::cout << std::endl;

    // skill 출력
    std::cout << "skill: " << my_poke.get_skill_name().at(0);
    for (int i=1; i<my_poke.get_skill_name().size(); i++) {
        std::cout << "/" << my_poke.get_skill_name().at(i);
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

Pokemon change_skill(Pokemon my_poke){
    std::ifstream ifs;
    std::string line;
    std::stringstream ss;
    std::vector <int> skill_id;
    std::vector <std::string> skill_name;
    std::vector <std::string> skill_type;
    std::vector <std::string> skill_as;
    ifs.open("pokeDB/skill_list.txt");
    while(!ifs.eof()){
        std::getline(ifs, line);
        ss << line;
        std::string data;

        std::getline(ss, data, '.');
        skill_id.push_back(std::stoi(data));

        std::getline(ss, data, ':');
        // 앞에 공백 제거
        if (data[0] == ' ') {
            data.erase(0, 1);
        }
        skill_name.push_back(data);

        std::getline(ss, data, ',');
        // 앞에 공백 제거
        if (data[0] == ' ') {
            data.erase(0, 1);
        }
        skill_type.push_back(data);

        std::getline(ss, data);
        // 앞에 공백 제거
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
        skill_as.push_back(data);

        ss.clear();
        ss.str("");
    }
    ifs.close();

    std::string select;
    int remove_target = -1;
    if (my_poke.get_skill_id().size() >= 4) {
        std::cout << my_poke.get_name() << " has learned ";
        for (int i=0; i<my_poke.get_skill_name().size(); i++){
            std::cout << i+1 << ". " << my_poke.get_skill_name().at(i) << " ";
        }
        std::cout << "\nwhich skill your pokemon want to replace? ";
        std::cin >> select;
        while (!is_number(select) || std::stoi(select) < 1 || std::stoi(select) > 4) {
            std::cout << "please insert appropriate number\n\n";
            return my_poke;
        }

        remove_target = std::stoi(select) - 1; // 0, 1, 2, 3 중 하나
    }
    
    for (int i=0; i<skill_name.size(); i++){
        std::cout << skill_id.at(i) << ". " << skill_name.at(i) << ": " << skill_type.at(i) << ", " << skill_as.at(i) << std::endl;
    }

    std::cout << "what skill your pokemon want to learn? ";
    std::cin >> select;
    while (!is_number(select) || std::stoi(select) < 1 || std::stoi(select) > 36) {
        std::cout << "please insert appropriate number\n\n";
        return my_poke;
    }

    int skill_count = 0;
    for (int i=0; i<my_poke.get_skill_id().size(); i++){
        if (my_poke.get_skill_id().at(i) == std::stoi(select)){
            std::cout << "already learned " << my_poke.get_skill_name().at(i) << std::endl;
            skill_count += 1;
            break;
        }
    }
    if (skill_count == 0){
        if (remove_target != -1) {
            my_poke.remove_skill(remove_target);
        }
        my_poke.add_skill(std::stoi(select));
    }
    std::cout << std::endl;
    return my_poke;
}

Pokemon configure(Pokemon my_poke){
    while(true){
        std::string select;
        std::cout << "select the operation among 1~4\n1. see pokemonDB\n2. see my pokemon's stat\n3. change my pokemon's skill\n4. exit from configuration mode\nselect: ";
        std::cin >> select;
        while (!is_number(select) || std::stoi(select) < 1 || std::stoi(select) > 4) {
            std::cout << "please insert appropriate number\nselect: ";
            std::cin >> select;
        }
        
        if (std::stoi(select) == 1){
            std::cout << std::endl;
            show_pokeDB();
        }
        else if (std::stoi(select) == 2){
            std::cout << std::endl;
            show_my_poke_stat(my_poke);
        }
        else if (std::stoi(select) == 3){
            std::cout << std::endl;
            my_poke = change_skill(my_poke);
        }
        else{
            break;
        }
    }
    return my_poke;
}