#include "defense_advisor.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>



// Select type from defensors that is the least common in player_defense_individuals_in_danger_zone
char DefenseAdvisor::select_individual_type(const std::vector<const Individual*>& player_defense_individuals_in_danger_zone, const std::set<char>& defensors){
    char defensor = *defensors.begin();
    int min_defensors = std::numeric_limits<int>::max();

    for(const char c : defensors){
        int defensors_of_type_c = count_if(player_defense_individuals_in_danger_zone.begin(), player_defense_individuals_in_danger_zone.end(), [c](const Individual* i) { return i->type == c; });
        if(defensors_of_type_c < min_defensors){
            defensor = c;
            min_defensors = defensors_of_type_c;
        }
    }

    return defensor;
}


// Select opponent's individual that is closest to individual
const Individual* DefenseAdvisor::find_nearest_opponent(const Individual* individual, std::vector<const Individual*>&  opponent_individuals){
    const Individual* nearest_opponent = opponent_individuals[0];
    int min_distance = std::numeric_limits<int>::max();

    for(const Individual* o : opponent_individuals){
        int distance_to_opponent = calculateDistance(individual->x_coordinate, individual->y_coordinate, std::make_pair(o->x_coordinate, o->y_coordinate));

        if(distance_to_opponent < min_distance){
            min_distance = distance_to_opponent;
            nearest_opponent = o;
        }
    }

    return nearest_opponent;
}

 /*
    Naive defense strategy
    Create danger zone around the player base - area of points that distance is less or equal the maximum individual's attack range, i,e 7.
    Find all opponent's individuals in the danger zone and attack them.
    Keep enough player's individuals in a danger zone.

    Heuristics:
    Preferred individual types:
    Archer
    Catapult
    Swordsman

*/ 
std::vector<std::unique_ptr<Command>> DefenseAdvisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;
    std::set<char> defensors({'A', 'C', 'S'});

    int danger_zone_length = 7;
    

    std::vector<const Individual*>  opponent_individuals_in_danger_zone;
    std::vector<const Individual*>  player_defense_individuals_in_danger_zone;

    for(const Individual* i : player_individuals){
        
        if(calculateDistance(i->x_coordinate, i->y_coordinate, std::make_pair(player_base->x_coordinate, player_base->y_coordinate)) <= danger_zone_length 
            && defensors.find(i->type) != defensors.end()){
            player_defense_individuals_in_danger_zone.push_back(i);
        } 
    }

    for(const Individual* i : opponent_individuals){
        
        if(calculateDistance(i->x_coordinate, i->y_coordinate, std::make_pair(player_base->x_coordinate, player_base->y_coordinate)) <= danger_zone_length){
            opponent_individuals_in_danger_zone.push_back(i);
        } 
    }
    
    // Set minimum bound of defensors in danger zone near base
    int possible_nr_of_attackers = opponent_individuals.size()/3;
    int minimum_defensors = 2 > possible_nr_of_attackers ? 2 : possible_nr_of_attackers;


    // Dangerous situation, enemy can attack the base
    // For all player_defense_individuals_in_danger_zone find nearest opponent, move towards them and attack
    if(opponent_individuals_in_danger_zone.size() > 0){
        for(const Individual* i : player_defense_individuals_in_danger_zone){
            const Individual* nearest_opponent = find_nearest_opponent(i, opponent_individuals_in_danger_zone);
            
            // Attack without move if opponent is within attack range
            if(calculateDistance(i->x_coordinate, i->y_coordinate, std::make_pair(nearest_opponent->x_coordinate, nearest_opponent->y_coordinate)) <= 
                Individual::statistics.find(i->type)->second.find("range")->second){
                commands.push_back(std::make_unique<Attack>(command_priority, i->id, nearest_opponent->id));
            }

            // Else move towards opponent
            else{
                std::pair<int, int> next_step = find_next_step(i, nearest_opponent);

                if(next_step.first != -1){
                    // Move towards
                    commands.push_back(std::make_unique<Move>(command_priority, i->id, next_step.first, next_step.second));

                    int distance_to_opponent = calculateDistance(nearest_opponent->x_coordinate, nearest_opponent->y_coordinate, next_step);
                    int distance_covered = calculateDistance(i->x_coordinate, i->y_coordinate, next_step);

                    // If individual has enough range to attack the opponent and has also one speed point after move then attack
                    if(distance_to_opponent <= Individual::statistics.find(i->type)->second.find("range")->second &&
                        distance_covered+1 <= Individual::statistics.find(i->type)->second.find("speed")->second){
                            commands.push_back(std::make_unique<Attack>(command_priority, i->id, nearest_opponent->id));
                    }
                }

                // If move is impossible than stay in danger zone
                else
                    commands.push_back(std::make_unique<Move>(command_priority, i->id, i->x_coordinate, i->y_coordinate));

            }
            

        }
    }
    // Safe situation - keep some individuals in a danger zone
    else{
        int defensors_to_keep = minimum_defensors;
        for(const Individual* i : player_defense_individuals_in_danger_zone){
            if(defensors_to_keep>0 && defensors.find(i->type) != defensors.end()){
                commands.push_back(std::make_unique<Move>(command_priority, i->id, i->x_coordinate, i->y_coordinate));
                defensors_to_keep--;
            }
        }
    }


    // Not sufficient number of defensors - Build order
    if(player_defense_individuals_in_danger_zone.size() < minimum_defensors){
        char defensor_to_build = select_individual_type(player_defense_individuals_in_danger_zone, defensors);
        commands.push_back(std::make_unique<Build>(command_priority, player_base->id, defensor_to_build));
    }
    

    return commands;
}