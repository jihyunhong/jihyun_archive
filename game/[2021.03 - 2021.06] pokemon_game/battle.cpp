#include "battle.hpp"
#include <iostream>
#include <cmath>

int compute_damage(Pokemon A, Pokemon B, int skill_id) {
    // 설명 : A 포켓몬이 B 포켓몬에게 skill_id에 해당하는 스킬 구사. 이 때의 데미지 계산
    
    // A 포켓몬의 스킬이 아닌 경우 exit(1)
    int temp = 0;
    int index = -1;
    for (int i=0; i<A.get_skill_id().size(); i++) {
        if (skill_id == A.get_skill_id().at(i)) {
            temp = 1;
            index = i; // 앞으로 이 함수에서 계속 쓸 친구
        }
    }
    if (!temp) {
        exit(1);
    }
    
    // 실제 능력치 = 종족값 + (86, 31, 31, 31, 31, 31)
    std::vector<int> modify = {86, 31, 31, 31, 31, 31};
    std::vector<int> A_stats = A.get_stats();
    std::vector<int> B_stats = B.get_stats();
    for (int i=0; i<modify.size(); i++) {
        A_stats.at(i) += modify.at(i);
        B_stats.at(i) += modify.at(i);
    }

    // 기본 공격값 계산
    float damage = 0;
    int a, d;
    if (A.get_skill_as().at(index) == "attack") {
        a = A_stats.at(1);
        d = B_stats.at(2);
    }
    else {
        a = A_stats.at(3);
        d = B_stats.at(4);
    }
    damage = 44.0 * a / d + 2.0;
    
    // main character 보정
    if (A.get_is_mine()) {
        damage *= 1.5;
    }
    
    // type 기술 보정 
    std::string skill_type = A.get_skill_type().at(index);
    for (int i=0; i<A.get_type_name().size(); i++) {
        if (skill_type == A.get_type_name().at(i)) {
            damage *= 1.5;
            break;
        }
    }
    
    // type 보정
    std::ifstream ifs;
    std::string line;
    std::stringstream ss;
    
    ifs.open("pokeDB/type_efficacy.csv");
    std::getline(ifs, line);
    
    while (!ifs.eof()) {
        std::getline(ifs, line);
        ss << line;
        std::string data;
        std::getline(ss, data, ',');
        if (!is_number(data)) {
            ss.clear();
            ss.str("");
            continue;
        }
        // std::stoi(data) 와 A.get_skill_type().at(index) match
        std::ifstream ifs2;
        std::string line2;
        std::stringstream ss2;
        ifs2.open("pokeDB/types.csv");
        std::getline(ifs2, line2);
        temp = 0;
        while (!ifs2.eof()) {
            std::getline(ifs2, line2);
            ss2 << line2;
            std::string data2;
            std::getline(ss2, data2, ',');
            if (!is_number(data2)) {
                ss2.clear();
                ss2.str("");
                continue;
            }
            if (std::stoi(data2) == std::stoi(data)) {
                std::getline(ss2, data2, ',');
                // remove carriage return
                for (int i=0; i<data2.size(); i++) {
                    if (data2[i] == '\r') {
                        data2.erase(i, 1);
                        break;
                    }
                }
                if (data2 == A.get_skill_type().at(index)) {
                    temp = 1;
                    break;
                }
                else {
                    temp = 0;
                    break;
                }
            }
            ss2.clear();
            ss2.str("");
        }
        ifs2.close();
        if (!temp) {
            ss.clear();
            ss.str("");
            continue;
        } 
        else {
            std::getline(ss, data, ',');
            for (int i=0; i<B.get_type_id().size(); i++) {
                if (std::stoi(data) == B.get_type_id().at(i)) {
                    std::getline(ss, data, ',');
                    damage *= (std::stoi(data) / 100.0);
                }
            }
        }
        ss.clear();
        ss.str("");
    }
    ifs.close();
    return ceil(damage);
}

void print_efficacy(Pokemon my_poke, Pokemon enemy) {
    int damage;

    std::cout << "your pokemon's efficacy to the enemy" << std::endl;
    for (int i=0; i<my_poke.get_skill_name().size(); i++) {
        damage = compute_damage(my_poke, enemy, my_poke.get_skill_id().at(i));
        std::cout << my_poke.get_skill_name().at(i) << " damage is " << damage << std::endl;
    }
    std::cout << "enemy's efficacy to your pokemon" << std::endl;
    for (int i=0; i<enemy.get_skill_name().size(); i++) {
        damage = compute_damage(enemy, my_poke, enemy.get_skill_id().at(i));
        std::cout << enemy.get_skill_name().at(i) << " damage is " << damage << std::endl;
    }
}

int battle_process(Pokemon my_poke, Pokemon enemy) {
    bool my_turn; // 1 if my turn, 0 if enemy's turn
    int damage;
    std::string skill_used;
    bool same_speed = false;
    
    if (my_poke.get_stats().at(5) > enemy.get_stats().at(5)) {
        my_turn = true;
    }
    else if (my_poke.get_stats().at(5) < enemy.get_stats().at(5)) {
        my_turn = false;
    }
    else {
        same_speed = true;
    }
    
    int battle_count = 0;
    int my_poke_hp_before = my_poke.get_stats().at(0) + 86;
    int my_poke_hp_after = my_poke_hp_before;
    int enemy_hp_before = enemy.get_stats().at(0) + 86;
    int enemy_hp_after = enemy_hp_before;
    while (battle_count < 20 && my_poke_hp_after > 0 && enemy_hp_after > 0) {
        if (same_speed) {
            my_turn = rand() % 2;
        }
        if (my_turn) {
            damage = -1;
            for (int i=0; i<my_poke.get_skill_name().size(); i++) {
                int _damage = compute_damage(my_poke, enemy, my_poke.get_skill_id().at(i));
                if (_damage > damage) {
                    damage = _damage;
                    skill_used = my_poke.get_skill_name().at(i);
                }
            }
            enemy_hp_after = enemy_hp_before - damage;
            if (enemy_hp_after < 0) {
                enemy_hp_after = 0;
            }
            std::cout << "your pokemon used " << skill_used << " to enemy" << std::endl;
            std::cout << "enemy's hp is decreased from " << enemy_hp_before << " to " << enemy_hp_after << std::endl;
            enemy_hp_before = enemy_hp_after;
            my_turn = false;
        }
        else {
            damage = -1;
            for (int i=0; i<enemy.get_skill_name().size(); i++) {
                int _damage = compute_damage(enemy, my_poke, enemy.get_skill_id().at(i));
                if (_damage > damage) {
                    damage = _damage;
                    skill_used = enemy.get_skill_name().at(i);
                }
            }
            my_poke_hp_after = my_poke_hp_before - damage;
            if (my_poke_hp_after < 0) {
                my_poke_hp_after = 0;
            }
            std::cout << "enemy used " << skill_used << " to your pokemon" << std::endl;
            std::cout << "your hp is decreased from " << my_poke_hp_before << " to " << my_poke_hp_after << std::endl;
            my_poke_hp_before = my_poke_hp_after;
            my_turn = true;
        }
        battle_count += 1;
    }
    
    int result; // 1 if I win, 0 if draw, -1 if enemy wins
    std::cout << std::endl;
    if (my_poke_hp_after > enemy_hp_after) {
        std::cout << "you defeated the enemy" << std::endl;
        result = 1;
    }
    else if (my_poke_hp_after < enemy_hp_after) {
        std::cout << "enemy defeated you" << std::endl;
        result = -1;
    }
    else {
        std::cout << "draw" << std::endl;
        result = 0;
    }
    return result;
}

Pokemon reward(Pokemon my_poke, Pokemon enemy) {
    // 현재 내가 이긴 상황
    // 가능한 리워드
    // 1. (디폴트) 적 능력 흡수
    // 2. 진화할지 말지
    // 3. 포켓몬 바꿀지 말지

    std::string selection;

    // overwhelm enemy
    for (int i=0; i<my_poke.get_stats().size(); i++) {
        if (enemy.get_stats().at(i) > my_poke.get_stats().at(i)) {
            my_poke.set_stats(i, enemy.get_stats().at(i));
        }
    }
    
    // determine whether evolve or not
    std::cout << std::endl;
    if (my_poke.get_evolve_to().size() != 0){
        std::cout << "Your pokemon can be evolved to ";
        for (int i=0; i<my_poke.get_evolve_to().size(); i++) {
            int _id = my_poke.get_evolve_to().at(i);
            std::ifstream ifs;
            std::string line;
            std::stringstream ss;
            std::string _name;
            ifs.open("pokeDB/pokemon_species.csv");
            std::getline(ifs, line);
            while (!ifs.eof()) {
                std::getline(ifs, line);
                ss << line;
                std::string data;
                std::getline(ss, data, ',');
                if (_id == std::stoi(data)) {
                    std::getline(ss, data, ',');
                    _name = data;
                    break;
                }
                ss.clear();
                ss.str("");
            }
            ifs.close();
            std::cout << i+1 << ". " << _name << " ";
        }
        std::cout << "\nWhich pokemon you want to be evolved to?\nselect the number above, select 0 if you don't want to evolve your pokemon\nselection: ";
        std::cin >> selection;
        while (!is_number(selection) || (std::stoi(selection) > my_poke.get_evolve_to().size()) || (std::stoi(selection) < 0)) {
            std::cout << "please insert appropriate number\nselection: ";
            std::cin >> selection;
        }
        if (std::stoi(selection) != 0) {
            std::vector<int> next_poke_init;
            next_poke_init.push_back(my_poke.get_evolve_to().at(std::stoi(selection) - 1));
            Pokemon next_poke(true, next_poke_init);
            for (int i=0; i<my_poke.get_stats().size(); i++) {
                if (next_poke.get_stats().at(i) < my_poke.get_stats().at(i)) {
                    next_poke.set_stats(i, my_poke.get_stats().at(i));
                }
            }
            // 원래의 스킬 보존 (pokemon evlove 된 후에도 원래 자신의 skill 보존)
            std::vector<int> _skill_id;
            std::vector<std::string> _skill_name;
            std::vector<std::string> _skill_type; // flying, normal
            std::vector<std::string> _skill_as; 
            for (int i=0; i<my_poke.get_skill_id().size(); i++){
                _skill_id.push_back(my_poke.get_skill_id().at(i));
                _skill_name.push_back(my_poke.get_skill_name().at(i));
                _skill_type.push_back(my_poke.get_skill_type().at(i));
                _skill_as.push_back(my_poke.get_skill_as().at(i));
            }

            my_poke = next_poke;
            for (int i=0; i<my_poke.get_skill_id().size(); i++){
                my_poke.swap_skill_id(_skill_id);
                my_poke.swap_skill_name(_skill_name);
                my_poke.swap_skill_type(_skill_type);
                my_poke.swap_skill_as(_skill_as);
            }
        }
    }
    
    // change pokemon
    std::cout << "Will you change your pokemon into enemy's pokemon? 1. yes 2. no\nselection: ";
    std::cin >> selection;
    while (!is_number(selection) || (std::stoi(selection) > 2 || (std::stoi(selection) < 1))) {
        std::cout << "please insert appropriate number\nselection: ";
        std::cin >> selection;
    }
    if (std::stoi(selection) == 1) {
        for (int i=0; i<my_poke.get_stats().size(); i++) {
            if (enemy.get_stats().at(i) < my_poke.get_stats().at(i)) {
                enemy.set_stats(i, my_poke.get_stats().at(i));
            }
        }
        my_poke = enemy;
    }
    return my_poke;
}

Pokemon battle(Pokemon my_poke) {
    
    std::vector<int> enemy_info = poke_generator();
    Pokemon enemy(false, enemy_info);
    enemy.print_poke_info();
    std::cout << std::endl;
    print_efficacy(my_poke, enemy);
    std::cout << std::endl;
    int result = battle_process(my_poke, enemy);
    if (result == 1) {
        my_poke = reward(my_poke, enemy);
    }
    
    return my_poke;
}