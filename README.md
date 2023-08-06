# Tieto recruitment task

## Project structure

    - main, runs the program
    - reader, reads map and status
    - individual, represents individuals from status
    - commands, represent commands move, attack, build
    - advisor, attack_advisor, defense_advisor, mine_advisor, elements of the game strategy, analyse map, status and generate commands
    - commander, merge commands, validates, check conditions and writes commands to file

## How to run

```
mkdir build
cd build
cmake ..
make
./play ../mapa.txt ../status.txt ../rozkazy.txt
```