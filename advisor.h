/*
    This class implements strategy for the game.
*/

#include <vector>
#include <memory>
#include "commands.h"
#include "individual.h"

class Advisor{
    public:
        Advisor(const std::vector<std::vector<char>>& r_game_map, const std::vector<Individual>& r_individuals) : game_map(r_game_map), individuals(r_individuals){}
        virtual std::vector<std::unique_ptr<Command>> advise();
    private:
        bool opponent_in_range(const Individual* individual, const Individual* opponent);
        const Individual* opponent_in_range(const Individual* individual, const std::vector<const Individual*>&  opponent_individuals);
        std::pair<int, int> next_step(const Individual* individual, const Individual* target); 
        const std::vector<std::vector<char>>& game_map; 
        const std::vector<Individual>& individuals;
};