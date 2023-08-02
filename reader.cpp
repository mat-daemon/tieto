#include "reader.h"
#include <fstream>
#include <iostream>

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


        for(const char& c : line){
            single_row.push_back(c);
        }

        game_map.push_back(std::move(single_row));
    }

    file.close();
}

void Reader::printMap(){
    for(const auto& single_row : game_map){
        for(const char& cell : single_row) std::cout<<cell<<" ";
        std::cout<<"\n";
    }
}