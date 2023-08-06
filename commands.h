#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

struct Command{
    Command(int c_priority) : priority(c_priority){}

    int priority;

    virtual std::string getCommand() const = 0;

    int get_priority() const;
    virtual char get_type() const = 0;
    virtual int get_subject() const = 0;
    bool operator<(const Command& c);    
};

struct Move : Command{
    Move(int c_priority, int i_id, int i_x, int i_y) : Command(c_priority), individual_id(i_id), x(i_x), y(i_y){}
    int individual_id;
    int x;
    int y;

    char get_type() const;
    int get_subject() const; 
    std::string getCommand() const;
};

struct Attack : Command{
    Attack(int c_priority, int attacker, int victim) : Command(c_priority), attacker_id(attacker), victim_id(victim){}
    int attacker_id;
    int victim_id;

    char get_type() const;
    int get_subject() const; 
    std::string getCommand() const; 
};

struct Build : Command{
    Build(int c_priority, int base, char individual) : Command(c_priority), base_id(base), individual_to_build(individual){}
    int base_id;
    char individual_to_build;

    char get_type() const;
    int get_subject() const; 
    std::string getCommand() const;
};

#endif /* COMMANDS_H */