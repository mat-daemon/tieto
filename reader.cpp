#include "reader.h"
#include <fstream>
#include <iostream>
#include <sstream>


int Reader::getGold(){return gold;};


void Reader::readMap(){
    std::ifstream file(map_path);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file '" << map_path << "'\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> single_row;

        for(const char& c : line){
            single_row.push_back(c);
        }

        game_map.push_back(std::move(single_row));
    }

    file.close();
}


void Reader::readStatus(){
    std::ifstream file(status_path);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file '" << status_path << "'\n";
        return;
    }

    std::string line;

    // read gold
    std::getline(file, line);
    gold = std::stol(line);

    // read individuals
    while (std::getline(file, line)) {
        std::vector<std::string> individual_parameters;
        
        std::istringstream ss(line);
 
        std::string word;

        while (ss >> word) {
            individual_parameters.push_back(std::move(word));
        }

        // individual representation formatting  - "owner type id x y stamina [i_production]"
        char i_owner = individual_parameters[0].c_str()[0];
        char i_type = individual_parameters[1].c_str()[0];
        int i_id = stoi(individual_parameters[2]);
        int i_x = stoi(individual_parameters[3]);
        int i_y = stoi(individual_parameters[4]);
        int i_stamina = stoi(individual_parameters[5]);

        // push base
        if(individual_parameters.size() == 7){
            char i_production = individual_parameters[6].c_str()[0];
            Individual individual(i_owner, i_type, i_id, i_x, i_y, i_stamina, i_production);
            individuals.push_back(std::move(individual));
        } 
        // push others
        else{
            Individual individual(i_owner, i_type, i_id, i_x, i_y, i_stamina);
            individuals.push_back(std::move(individual));
        }
        
    }

    file.close();
}

const std::vector<std::vector<char>>& Reader::showMap(){
    return game_map;
}

const std::vector<Individual>& Reader::showIndividuals(){
    return individuals;
}

// Debugging purpose
void Reader::printMap(){
    for(const auto& single_row : game_map){
        for(const char& cell : single_row) std::cout<<cell<<" ";
        std::cout<<"\n";
    }
}

void Reader::printIndividuals(){
    for(const auto& individual : individuals){
        std::cout<<individual.owner<<" "<<individual.type<<" "<<individual.id<<" "<<individual.x_coordinate<<" "<<individual.y_coordinate<<" "<<individual.stamina<<"\n";
    }
}