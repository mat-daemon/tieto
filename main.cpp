#include "reader.h"

int main(){
    Reader reader("mapa.txt", "status.txt");

    reader.readMap();
    reader.printMap();
}