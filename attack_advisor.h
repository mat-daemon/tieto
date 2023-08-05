#include "advisor.h"


class AttackAdvisor : Advisor{
    public:
        AttackAdvisor(int priority, const std::vector<std::vector<char>>& r_game_map, const std::vector<const Individual*>& r_player_individuals, 
        const std::vector<const Individual*>& r_opponent_individuals, const Individual* p_player_base, const Individual* p_opponent_base) 
        : Advisor(r_game_map, r_player_individuals, r_opponent_individuals, p_player_base, p_opponent_base), 
        command_priority(priority) {}
        std::vector<std::unique_ptr<Command>> advise();
    private:
        int command_priority;
};