#include <memory>
#include <fstream>
#include <iostream>
#include "commander.h"
#include "advisor.h"
#include "attack_advisor.h"


Commander::Commander(const std::string& map_path, const std::string& status_path, const std::string& commands_path)
 : reader(map_path, status_path), path_to_commands(commands_path){
    reader.readMap();
    reader.readStatus();

}

void Commander::generateCommands(){
    std::cout<<"Start generating commands\n";

    char player = 'P';
    char opponent = 'E';


    // Split individuals
    // It is safe using raw pointers, because individuals exist during program lifetime in the Reader
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

    AttackAdvisor attack_advisor(50, reader.showMap(), player_individuals, opponent_individuals, player_base, opponent_base);

    std::priority_queue<std::unique_ptr<Command>> commands_register;
    
    std::cout<<"Attack advisor advising\n";

    std::vector<std::unique_ptr<Command>> attack_commands(attack_advisor.advise());

    for(auto& c : attack_commands) commands_register.push(std::move(c));


    std::ofstream out(path_to_commands);

    while(!commands_register.empty()){
        auto const& c = commands_register.top();
        std::cout<<c->getCommand()<<"\n";
        out << c->getCommand() <<"\n";
        commands_register.pop();
    }
    

    out.close();
}