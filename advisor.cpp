#include <map>
#include "advisor.h"


std::vector<std::unique_ptr<Command>> Advisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;

    commands.push_back(std::make_unique<Move>(60, 1, 10, 12));
    commands.push_back(std::make_unique<Attack>(50, 1, 2));
    commands.push_back(std::make_unique<Build>(70, 1, 'C'));

    char player = 'P';
    char opponent = 'E';

    const Individual* player_base;
    const Individual* opponent_base;

    std::map<std::pair<int, int>, const Individual&> opponent_individuals;
    std::vector<const Individual&> player_individuals;

    /*
        Attack naive strategy
        If player's individual can attack the base then attack.
        Attack advisor adds constant priority to every command as attack is the main objective.
        If opponent's individual is within the attack range, then check if one is stronger. When stronger then push to base else attack and fight.  
        Else push the base.
    */ 

   for(const Individual& i : individuals){
        if(i.owner == player){
            if(i.type == 'B') player_base = &i;
            else{
                player_individuals.push_back(i);
            }
        }
        else{
            if(i.type == 'B') opponent_base = &i;
            else{
                
            }
        }
   }

    return commands;
}