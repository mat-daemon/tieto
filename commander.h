/*
    This class implements the commander - general strategy director of a game.
    Commander has three subdivisions:
    -attack
    -defense
    -mining
*/
#include <string>
#include <queue>
#include "commands.h"
#include "reader.h"


class Commander{
    public:
        Commander(const std::string& map_path, const std::string& status_path, const std::string& commands_path);
        void generateCommands();

    private:
        const std::string& path_to_commands;
        std::priority_queue<Command> commands;
        Reader reader;
};