#include "attack_advisor.h"
#include <iostream>
#include <limits>
#include <algorithm>


// Select type from attackers that is the least common in player_attack_individuals
char AttackAdvisor::select_individual_type(const std::vector<const Individual*>& player_attack_individuals, const std::set<char>& attackers){
    char attacker = *attackers.begin();
    int min_attackers = std::numeric_limits<int>::max();

    for(const char c : attackers){
        int attackers_of_type_c = count_if(player_attack_individuals.begin(), player_attack_individuals.end(), [c](const Individual* i) { return i->type == c; });
        if(attackers_of_type_c < min_attackers){
            attacker = c;
            min_attackers = attackers_of_type_c;
        }
    }

    return attacker;
}

 /*
        Naive attack strategy
        If player's individual can attack the base then attack.
        Attack advisor adds constant priority to every command as attack is the main objective.
        If opponent's individual is within the attack range, then check if one is stronger. When stronger then push to base else attack and fight.  
        Else push the base.
        Attack advisor advise every player's individual to attack - he is very insistent.
        Other advisors can override his decisions when they have higher priority.
*/ 
std::vector<std::unique_ptr<Command>> AttackAdvisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;

    std::set<char> attackers({'K', 'P', 'R'});
    std::vector<const Individual*>  player_attackers;

    for(const Individual* i : player_individuals){
        if(attackers.find(i->type) != attackers.end()) player_attackers.push_back(i);

        if(opponent_in_range(i, opponent_base)){
            std::cout<<"Base in range: "<<command_priority<<" "<< i->id<<" "<< opponent_base->id<<"\n";
            commands.push_back(std::make_unique<Attack>(command_priority, i->id, opponent_base->id));
        } 

        else{
            const Individual* opponent_in_range = find_opponent_in_range(i);

            if(opponent_in_range != nullptr) {
                std::cout<<"Opponent in range: "<<command_priority<<" "<< i->id<<" "<< opponent_in_range->id<<"\n";
                commands.push_back(std::make_unique<Attack>(command_priority, i->id, opponent_in_range->id));
            }

            else{
                std::pair<int, int> next_step = find_next_step(i, opponent_base);
                std::cout<<"Next step: "<<command_priority<<" "<< i->id<<" "<< next_step.first<< " "<<next_step.second<<"\n";
                if(next_step.first!=-1) commands.push_back(std::make_unique<Move>(command_priority, i->id, next_step.first, next_step.second));
            }
        }


    }
    
    // Always want more attackers
    char attacker_to_build = select_individual_type(player_attackers, attackers);
    commands.push_back(std::make_unique<Build>(command_priority, player_base->id, attacker_to_build));

    return commands;
}