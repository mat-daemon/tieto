#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

/*
    This struct implements an individual entity that exists in a game
*/
#include <map>
#include <string>

class Individual{
    public:
        static const std::map<char, std::map<std::string, int>> statistics;

        static const std::map<char, std::map<char, int>> attack_table;

        Individual(char i_owner, char i_type, int i_id, int i_x, int i_y, int i_stamina, char i_production='0') :
            owner(i_owner), type(i_type), id(i_id), x_coordinate(i_x), y_coordinate(i_y), stamina(i_stamina), production(i_production){}
  
        int id;
        char type;
        char owner;
        int x_coordinate;
        int y_coordinate;
        int stamina;
        char production;

};

#endif