#include "attack_advisor.h"
#include <iostream>

 /*
        Naive attack strategy
        If player's individual can attack the base then attack.
        Attack advisor adds constant priority to every command as attack is the main objective.
        If opponent's individual is within the attack range, then check if one is stronger. When stronger then push to base else attack and fight.  
        Else push the base.
*/ 
std::vector<std::unique_ptr<Command>> AttackAdvisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;


    for(const Individual* i : player_individuals){
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
    


    return commands;
}