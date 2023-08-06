#include <memory>
#include <fstream>
#include <iostream>
#include <map>
#include "commander.h"
#include "advisor.h"
#include "attack_advisor.h"
#include "defense_advisor.h"
#include "mine_advisor.h"


Commander::Commander(const std::string& map_path, const std::string& status_path, const std::string& commands_path)
 : reader(map_path, status_path), path_to_commands(commands_path){
    reader.readMap();
    reader.readStatus();

}

class CompareCommands {
public:
  bool operator()(const std::unique_ptr<Command>& a, const std::unique_ptr<Command>& b) {
    return a->get_priority() < b->get_priority();
  }
};


void Commander::generateCommands(){
    std::cout<<"Start generating commands\n";

    char player = 'P';
    char opponent = 'E';


    // Split individuals
    // It is safe to use raw pointers, because individuals exist during program lifetime in the Reader
    // Also player_base and opponent_base have to exist.
    const Individual* player_base;
    const Individual* opponent_base;
    
    std::vector<const Individual*>  opponent_individuals;
    std::vector<const Individual*> player_individuals;

    const std::vector<Individual>& individuals = reader.showIndividuals();


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

    /*
    std::cout<<"Individuals:"<<"\n";
    for(const Individual& i : individuals){
        std::cout<<i.id<<" "<<i.type<<" "<<i.x_coordinate<<" "<<i.y_coordinate<<"\n";
    }
    std::cout<<"Player individuals:"<<"\n";
    for(const Individual* i : player_individuals){
        std::cout<<i->id<<" "<<i->type<<" "<<i->x_coordinate<<" "<<i->y_coordinate<<"\n";
    }
    std::cout<<"Opponent individuals:"<<"\n";
    for(const Individual* i : opponent_individuals){
        std::cout<<i->id<<" "<<i->type<<" "<<i->x_coordinate<<" "<<i->y_coordinate<<"\n";
    }
    */

    /* Create advisors
        - attack priority 60
        - defense priority 100
        - mine priority 70
    */
    AttackAdvisor attack_advisor(60, reader.showMap(), player_individuals, opponent_individuals, player_base, opponent_base);
    DefenseAdvisor defense_advisor(100, reader.showMap(), player_individuals, opponent_individuals, player_base, opponent_base);
    MineAdvisor mine_advisor(70, reader.showMap(), player_individuals, opponent_individuals, player_base, opponent_base);

    // Additional comparator must exist when storing unique_ptr
    std::priority_queue<std::unique_ptr<Command>, std::vector<std::unique_ptr<Command>>, CompareCommands> commands_register;

    // Each advisor makes its strategy
    std::vector<std::unique_ptr<Command>> attack_commands(attack_advisor.advise());
    std::vector<std::unique_ptr<Command>> defense_commands(defense_advisor.advise());
    std::vector<std::unique_ptr<Command>> mine_commands(mine_advisor.advise());

    for(auto& c : attack_commands) commands_register.push(std::move(c));
    for(auto& c : defense_commands) commands_register.push(std::move(c));
    for(auto& c : mine_commands) commands_register.push(std::move(c));
    

    /* Individual can be built only when:
        - there is enough gold
        - base is not producing
        - only one build can be ordered
    */
    const int gold = reader.getGold();
    bool is_base_building = (player_base->production != '0');

    // Only one attack per turn
    bool attack_ordered = false;

    // Each individual can be controlled only by the same priority
    std::map<int, int> individuals_priority;

    std::ofstream out(path_to_commands);


    // Consider commands in priority order
    while(!commands_register.empty()){
        auto const& c = commands_register.top();
        
        std::cout<<c->getCommand()<<"\n";
        
        // Consider build
        if(c->get_type() == 'B'){
            if(!is_base_building){
                char type_to_build = c->getCommand().back();

                // If enough gold then build
                if(gold >= Individual::statistics.find(type_to_build)->second.find("cost")->second){
                    out << c->getCommand() <<"\n";
                    is_base_building = true;
                }
                // If not enough gold, then wait for more gold
                else is_base_building = true;               
            }
        }
        
        else{
            int individual_id = c->get_subject();

            /* 
                If command with same priority was previously added then add also the next command.
                It applies to combination of move + attack commands.
                More than one advisor can advise an individual to move or attack, but those commands cannot be mixed.
                So regarding one individual only such combinations are possible:
                    - move 
                    - attack
                    - move + attack
            */
            if(individuals_priority.find(individual_id) != individuals_priority.end()){
                if(individuals_priority[individual_id] == c->get_priority()) out << c->getCommand() <<"\n";
            }

            else{
                individuals_priority.insert({individual_id, c->get_priority()});
                out << c->getCommand() <<"\n";
            }
            
        }
        
        commands_register.pop();
    }
    

    out.close();
}