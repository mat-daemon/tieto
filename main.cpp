#include <iostream>
#include <string>
#include "commander.h"

/*
    The program makes an assumption that every provided data is correct,
    i.e. number of provided arguments (paths) is correct, given files exist and have valid format, etc.
    These points are not checked, so the program is not fault-tolerant.
*/

int main(int argc, char* argv[]){
    std::string map_path(argv[1]);
    std::string status_path(argv[2]);
    std::string commands_path(argv[3]);

    
    //Commander
    Commander commander(map_path, status_path, commands_path);
    commander.generateCommands();
}