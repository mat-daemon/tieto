#include <memory>
#include <fstream>
#include "commander.h"
#include "advisor.h"


Commander::Commander(const std::string& map_path, const std::string& status_path, const std::string& commands_path)
 : reader(map_path, status_path), path_to_commands(commands_path){
    reader.readMap();
    reader.readStatus();

}

void Commander::generateCommands(){
    Advisor advisor(reader.showMap(), reader.showIndividuals());

    std::priority_queue<std::unique_ptr<Command>> pq;
    std::vector<std::unique_ptr<Command>> attack_commands(advisor.advise());

    for(auto& c : attack_commands) pq.push(std::move(c));


    std::ofstream out(path_to_commands);

    while(!pq.empty()){
        auto const& c = pq.top();
        out << c->getCommand() <<"\n";
        pq.pop();
    }
    

    out.close();
}