/*
    This class implements tools that read mapa.txt and status.txt files to memory
*/

#include <vector>
#include <string>
#include "individual.h"

class Reader{
    public:
        Reader(const std::string& path_to_map, const std::string& path_to_status) : map_path(path_to_map), status_path(path_to_status){}
        void readMap();
        void readStatus();
        void printMap();

    private:
        const std::string& map_path;
        const std::string& status_path;
        std::vector<std::vector<char>> game_map;
        long gold;
        std::vector<char> individuals;
};