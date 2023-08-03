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
        std::vector<std::unique_ptr<Command>> advise();
    private:
        const std::vector<std::vector<char>>& game_map; 
        const std::vector<Individual>& individuals;
};