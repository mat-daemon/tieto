#include <iostream>
#include <string>
#include "commander.h"

int main(int argc, char* argv[]){
    std::string map_path(argv[1]);
    std::string status_path(argv[2]);
    std::string commands_path(argv[3]);

    
    //Commander
    Commander commander(map_path, status_path, commands_path);
    commander.generateCommands();
}