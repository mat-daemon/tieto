#include <iostream>
#include <limits>
#include "mine_advisor.h"


// Find mines that are not occupied by enemy
std::vector<std::pair<int, int>> MineAdvisor::find_mines(){
    int rows = game_map.size();
    int columns = game_map[0].size();
    char mine_sign = '6';
    std::vector<std::pair<int, int>> coordinates;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(game_map[i][j] == mine_sign){
                bool mine_available = true;

                for(const Individual* opponent : opponent_individuals)
                    if(opponent->x_coordinate == i && opponent->y_coordinate == j) mine_available = false;
                
                if(mine_available) coordinates.push_back(std::make_pair(i, j));
            }
        }
    }

    return coordinates;
}

std::pair<int, int> MineAdvisor::find_nearest_mine(const Individual* individual, const std::vector<std::pair<int, int>>& mines){
    int min_distance = std::numeric_limits<int>::max();
    std::pair<int, int> nearest_mine{-1, -1};

    for(const std::pair<int, int>& mine : mines){
        int distance = calculateDistance(individual->x_coordinate, individual->y_coordinate, mine);

        if(distance < min_distance){
            min_distance = distance;
            nearest_mine = mine;
        }
    }

    return nearest_mine;
}

 /*
    Naive mine strategy
    Move workers to the nearest mine.
*/ 
std::vector<std::unique_ptr<Command>> MineAdvisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;

    // TODO: delete magic numbers
    char mine_sign = '6';
    int miners_nr = 0;
    int minimum_miners = player_individuals.size()/4;

    std::vector<std::pair<int, int>> mines = find_mines();

    for(const Individual* i : player_individuals){
        if(i->type == 'W'){
            miners_nr++;

            // If miner is not in a mine
            if(!(game_map[i->x_coordinate][i->y_coordinate] == mine_sign)){
                std::pair<int, int> nearest_mine = find_nearest_mine(i, mines);

                if(nearest_mine.first != -1){
                    
                    // Worker can jump on the mine
                    if(calculateDistance(i->x_coordinate, i->y_coordinate, nearest_mine) <= Individual::statistics.find(i->type)->second.find("speed")->second){
                        commands.push_back(std::make_unique<Move>(command_priority, i->id, nearest_mine.first, nearest_mine.second));
                    }

                    else{
                         // TODO: very bad hackish conversion, should be repaired
                        Individual artificial_mine('N', 'N', -1, nearest_mine.first, nearest_mine.second, 1);
                        std::pair<int, int> next_step = find_next_step(i, &artificial_mine);

                        if(next_step.first != -1){
                            commands.push_back(std::make_unique<Move>(command_priority, i->id, next_step.first, next_step.second));
                        }    
                    }
                    
                }
               
            }
            // Else stay in a mine
            else commands.push_back(std::make_unique<Move>(command_priority, i->id, i->x_coordinate, i->y_coordinate));
        } 
    }

    if(miners_nr < minimum_miners) commands.push_back(std::make_unique<Build>(command_priority, player_base->id, 'W'));
    

    return commands;
}