# Tieto recruitment task

## Project structure

    - main; runs the program
    - reader; reads map and status
    - individual; represents individuals from status
    - commands; represent commands move, attack, build
    - advisor, attack_advisor, defense_advisor, mine_advisor; elements of the game strategy, analyse map, status and generate commands
    - commander; merge commands, validates, check conditions and writes commands to file

    - game_tests; some game states examples to check the programme, not real tests 

## Idea
1. Read map and status
1. Create three advisors: defense, attack and mining
1. Each advisor analyzes game status and creates commands with particular priority
1. Commander merges all commands from advisors
1. Commander chooses commands with highest priority that are in accordance to the game rules
1. Finally commander saves commands to the provided file

## How to run

```
mkdir build
cd build
cmake ..
make
./play ../mapa.txt ../status.txt ../rozkazy.txt
```

Author: Mateusz Śmigielski