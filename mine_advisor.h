#include "advisor.h"


class MineAdvisor : Advisor{
    public:
        MineAdvisor(int priority, const std::vector<std::vector<char>>& r_game_map, const std::vector<const Individual*>& r_player_individuals, 
        const std::vector<const Individual*>& r_opponent_individuals, const Individual* p_player_base, const Individual* p_opponent_base) 
        : Advisor(r_game_map, r_player_individuals, r_opponent_individuals, p_player_base, p_opponent_base), 
        command_priority(priority) {}
        std::vector<std::unique_ptr<Command>> advise();
    private:
        int command_priority;
        std::vector<std::pair<int, int>> find_mines();
        std::pair<int, int> find_nearest_mine(const Individual* individual, const std::vector<std::pair<int, int>>& mines);
};