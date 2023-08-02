#include <string>
#include "individual.h"


const std::map<char, std::map<std::string, int>> Individual::statistics = {
    {'K', {{"stamina", 70}, {"speed", 5}, {"cost", 400}, {"range", 1}, {"build_time", 5}} }, 
    {'S', {{"stamina", 60}, {"speed", 2}, {"cost", 250}, {"range", 1}, {"build_time", 3}} }, 
    {'A', {{"stamina", 40}, {"speed", 2}, {"cost", 250}, {"range", 5}, {"build_time", 3}} }, 
    {'P', {{"stamina", 50}, {"speed", 2}, {"cost", 200}, {"range", 2}, {"build_time", 3}} }, 
    {'R', {{"stamina", 90}, {"speed", 2}, {"cost", 500}, {"range", 1}, {"build_time", 4}} }, 
    {'C', {{"stamina", 50}, {"speed", 2}, {"cost", 800}, {"range", 7}, {"build_time", 6}} }, 
    {'W', {{"stamina", 20}, {"speed", 2}, {"cost", 100}, {"range", 1}, {"build_time", 2}} }, 
    {'B', {{"stamina", 20}, {"speed", 0}} }
};

const std::map<char, std::map<char, int>> attack_table = {
    {'K', {{'K', 35}, {'S', 35}, {'A', 35}, {'P', 35}, {'C', 35}, {'R', 50}, {'W', 35}, {'B', 35}} },
    {'S', {{'K', 30}, {'S', 30}, {'A', 30}, {'P', 20}, {'C', 20}, {'R', 30}, {'W', 30}, {'B', 30}} },
    {'A', {{'K', 15}, {'S', 15}, {'A', 15}, {'P', 15}, {'C', 10}, {'R', 10}, {'W', 15}, {'B', 15}} },
    {'P', {{'K', 35}, {'S', 15}, {'A', 15}, {'P', 15}, {'C', 15}, {'R', 10}, {'W', 15}, {'B', 10}} },
    {'C', {{'K', 40}, {'S', 40}, {'A', 40}, {'P', 40}, {'C', 40}, {'R', 40}, {'W', 40}, {'B', 50}} },
    {'R', {{'K', 10}, {'S', 10}, {'A', 10}, {'P', 10}, {'C', 10}, {'R', 10}, {'W', 10}, {'B', 50}} },
    {'W', {{'K', 5 }, {'S', 5 }, {'A', 5 }, {'P', 5 }, {'C', 5 }, {'R', 5 }, {'W', 5 }, {'B', 1 }} }
};