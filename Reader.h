//
// Created by Dima on 17.12.2021.
//
#include "Core.h"
#include "Commands.h"
#include "deque"

#ifndef INTERPRETER_READER_H
#define INTERPRETER_READER_H
using namespace std;

class Reader
{
    Commands &commands;
    Core &core;
    deque<int> callStack; // addresses

public:
    Reader(Core &core, Commands &commands) : core(core), commands(commands) {}

    void interpretFile(const string &fName); // reads file and creates commands with it, runs those commands
    void interactiveMode();                  // creates commands, then in endless loop ads command or block of commands and runs them

private:
    void runAllCommands();   // goes through all commands starting from current address and runs them
    bool runCommandOnCore(); // decodes string command and runs corresponding core method
    /* if it encounters:
     *     if : checks the condition and skips to the block end if it is false. Otherwise pushes if onto callStack and returns
     *     while : checks condition and skips to the block end if it is false. Otherwise pushes while onto callStack and returns
     *     for : checks if number is not 0, pushes for onto callStack and returns
     *     } : pops callStack and checks for type:
     *         if : skips
     *         while : goes back to the adress
     *         for : decrements number in front of for command, goes back to the address
     */
};

#endif // INTERPRETER_READER_H
