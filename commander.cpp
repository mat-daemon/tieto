#include "commander.h"

Commander::Commander(const std::string& map_path, const std::string& status_path, const std::string& commands_path) : reader(map_path, status_path){
    reader.readMap();
    reader.readStatus();

    reader.printMap();
    reader.printIndividuals();
}