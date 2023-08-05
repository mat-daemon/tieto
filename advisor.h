#ifndef ADVISOR_H
#define ADVISOR_H

/*
    This class implements strategy for the game.
*/

#include <vector>
#include <memory>
#include "commands.h"
#include "individual.h"

class Advisor{
    public:
        Advisor(const std::vector<std::vector<char>>& r_game_map, const std::vector<const Individual*>& r_player_individuals, 
        const std::vector<const Individual*>& r_opponent_individuals, const Individual* p_player_base, const Individual* p_opponent_base) 
        : game_map(r_game_map), player_individuals(r_player_individuals), opponent_individuals(r_opponent_individuals), player_base(p_player_base), opponent_base(p_opponent_base) {}
        
        virtual std::vector<std::unique_ptr<Command>> advise() = 0;
    
    protected:
        struct cell {
            int parent_i, parent_j;
            unsigned int f, g, h;
        };
        // A Utility Function to check whether given cell (row, col)
        // is a valid cell or not.
        inline bool isValid(int row, int col, int row_nr, int col_nr)
        {
            return (row >= 0) && (row < row_nr) && (col >= 0)
                && (col < col_nr);
        }

        inline bool isDestination(int row, int col, std::pair<int,int> dest)
        {
            return (row == dest.first && col == dest.second);
        }

        inline int calculateDistance(int row, int col, std::pair<int,int> dest)
        {
            return abs(row-dest.first) + abs(col-dest.second);
        }

        bool opponent_in_range(const Individual* individual, const Individual* opponent);
        const Individual* find_opponent_in_range(const Individual* individual);
        std::pair<int, int> find_furthest_point_in_path_within_range(const Individual* individual, const Individual* target, const std::vector<std::vector<cell>>& cell_details);
        std::pair<int, int> find_next_step(const Individual* individual, const Individual* target); 
        const std::vector<std::vector<char>>& game_map; 
        const Individual* player_base;
        const Individual* opponent_base;
        const std::vector<const Individual*>&  opponent_individuals;
        const std::vector<const Individual*>& player_individuals;
};


#endif