#include <sstream>
#include "commands.h"


bool Command::operator<(const Command& c){
    return priority < c.priority;
}    

int Command::get_priority () const{
    return priority;
}    

char Move::get_type() const{
    return 'M';
}

char Attack::get_type() const{
    return 'A';
}

char Build::get_type() const{
    return 'B';
}

int Move::get_subject() const{
    return individual_id;
}

int Attack::get_subject() const{
    return attacker_id;
}

int Build::get_subject() const{
    return base_id;
}

std::string Move::getCommand() const{
    std::stringstream ss;
    ss<< individual_id << " " << "M "<< x << " " << y;
    return ss.str();
}

std::string Attack::getCommand() const{
    std::stringstream ss;
    ss<< attacker_id << " " << "A "<< victim_id;
    return ss.str();
}

std::string Build::getCommand() const{
    std::stringstream ss;
    ss<< base_id << " " << "B "<< individual_to_build;
    return ss.str();
}