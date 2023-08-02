#include <fstream>
#include "commander.h"

Commander::Commander(const std::string& map_path, const std::string& status_path, const std::string& commands_path)
 : reader(map_path, status_path), path_to_commands(commands_path){
    reader.readMap();
    reader.readStatus();

    reader.printMap();
    reader.printIndividuals();
}

void Commander::generateCommands(){
    Move m(1, 10, 12);
    Attack a(1, 2);
    Build b(1, 'C');

    std::ofstream out(path_to_commands);
    out << m.getCommand() <<"\n" << a.getCommand() << "\n" <<b.getCommand();

    out.close();
}