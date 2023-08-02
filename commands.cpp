#include <sstream>
#include "commands.h"


bool Command::operator<(const Command& c){
    return priority < c.priority;
}    

std::string Move::getCommand(){
    std::stringstream ss;
    ss<< individual_id << " " << "M "<< x << " " << y;
    return ss.str();
}

std::string Attack::getCommand(){
    std::stringstream ss;
    ss<< attacker_id << " " << "A "<< victim_id;
    return ss.str();
}

std::string Build::getCommand(){
    std::stringstream ss;
    ss<< base_id << " " << "B "<< individual_to_build;
    return ss.str();
}