#include <map>
#include <iostream>
#include "advisor.h"


bool Advisor::opponent_in_range(const Individual* individual, const Individual* opponent){
    int range = Individual::statistics.find(individual->type)->second.find("range")->second;

    int distance_to_opponent = abs(opponent->x_coordinate - individual->x_coordinate) + abs(opponent->y_coordinate - individual->y_coordinate);

    return range >= distance_to_opponent;
}

const Individual* Advisor::opponent_in_range(const Individual* individual, const std::vector<const Individual*>&  opponent_individuals){
    for(const Individual* opponent : opponent_individuals){
        if(opponent_in_range(individual, opponent)) return opponent;
    }
}

std::pair<int, int> next_step(const Individual* individual, const Individual* target){
    

}



std::vector<std::unique_ptr<Command>> Advisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;

    commands.push_back(std::make_unique<Move>(60, 1, 10, 12));
    commands.push_back(std::make_unique<Attack>(50, 1, 2));
    commands.push_back(std::make_unique<Build>(70, 1, 'C'));


    /*
        Naive attack strategy
        If player's individual can attack the base then attack.
        Attack advisor adds constant priority to every command as attack is the main objective.
        If opponent's individual is within the attack range, then check if one is stronger. When stronger then push to base else attack and fight.  
        Else push the base.
    */ 

    char player = 'P';
    char opponent = 'E';


    // Split individuals
    // It is safe using raw pointers, because individuals exists during program lifetime in the Reader
    const Individual* player_base;
    const Individual* opponent_base;
    
    std::vector<const Individual*>  opponent_individuals;
    std::vector<const Individual*> player_individuals;


    for(const Individual& i : individuals){
        if(i.owner == player){
            if(i.type != 'B') player_individuals.push_back(&i);
            else player_base = &i;
        }
        else{
                if(i.type != 'B') opponent_individuals.push_back(&i);
                else opponent_base = &i;
        }
    }

    
    for(const Individual* i : player_individuals){
        
    }

    return commands;
}