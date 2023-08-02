#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

struct Command{
    int priority;

    virtual std::string getCommand() = 0;

    bool operator<(const Command& c);    
};

struct Move : Command{
    Move(int i_id, int i_x, int i_y) : individual_id(i_id), x(i_x), y(i_y){}
    int individual_id;
    int x;
    int y;

    std::string getCommand();
};

struct Attack : Command{
    Attack(int attacker, int victim) : attacker_id(attacker), victim_id(victim){}
    int attacker_id;
    int victim_id;

    std::string getCommand();
    
};

struct Build : Command{
    Build(int base, char individual) : base_id(base), individual_to_build(individual){}
    int base_id;
    char individual_to_build;

    std::string getCommand();
};

#endif /* COMMANDS_H */