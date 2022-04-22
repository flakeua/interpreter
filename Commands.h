//
// Created by Dima on 22.12.2021.
//

#ifndef INTERPRETER_COMMANDS_H
#define INTERPRETER_COMMANDS_H
#include "vector"
using namespace std;
// Used to store program commands and know where the interpreter is right now
class Commands
{
    int current_address = 0;
    vector<string> commands;

public:
    void addCommands(string commands0); // adds commands to the command vector, removes unneeded spaces

    void jumpToCommand(int address);

    int getCurrentAddress() { return current_address; }
    string getCurrentCommand();
    string nextCommand(); // returns next command and moves to it
    int findBlockEnd();   // finds corresponding closing curly brace
    void decrementForNumber();

    vector<string> getCommands() { return commands; }

private:
};

#endif // INTERPRETER_COMMANDS_H
