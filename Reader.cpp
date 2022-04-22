//
// Created by Dima on 23.12.2021.
//

#include "Reader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
void Reader::interpretFile(const string &fName)
{
    ifstream file(fName);
    if (!file.is_open())
    {
        throw runtime_error("File does not exist: " + fName);
    }
    string fileString;
    ostringstream ss;
    ss << file.rdbuf();
    fileString = ss.str();
    commands.addCommands(fileString);
    runAllCommands();
}

void Reader::interactiveMode()
{
    while (true)
    {
        string command_block = "";
        cout << "\n>>";
        getline(cin, command_block);
        bool hadCommands = true;
        try
        {
            commands.getCurrentCommand();
        }
        catch (out_of_range)
        {
            hadCommands = false;
        }
        commands.addCommands(command_block);
        if (hadCommands)
        {
            commands.nextCommand();
        }
        int lastAdress = commands.getCurrentAddress();
        int balance = 0;
        while (true)
        {
            try
            {
                string com = commands.nextCommand();
                if (com == "{")
                {
                    balance++;
                }
                if (com == "}")
                {
                    balance--;
                }
            }
            catch (out_of_range)
            {
                string curCom = commands.getCurrentCommand();
                if (balance == 0 && curCom.substr(0, 3) != "for" && curCom.substr(0, 5) != "while" && curCom.substr(0, 2) != "if")
                {
                    commands.jumpToCommand(lastAdress);
                    break;
                }
                string cb = "";
                cout << "\n>>";
                getline(cin, cb);
                commands.addCommands(cb);
            }
        }
        runAllCommands();
    }
}

void Reader::runAllCommands()
{
    while (true)
    {
        if (runCommandOnCore())
        {
            try
            {
                commands.nextCommand();
            }
            catch (out_of_range)
            {
                return;
            }
        }
    }
}

bool Reader::runCommandOnCore()
{
    string command = commands.getCurrentCommand();

    // if
    if (command.substr(0, 2) == "if")
    {
        if (commands.nextCommand() != "{")
        {
            throw runtime_error("blocks should start with \'{\'");
        }
        if (core.isCurrentZero())
        {
            int blockEnd = commands.findBlockEnd();
            commands.jumpToCommand(blockEnd);
        }
        else
        {
            callStack.push_back(commands.getCurrentAddress() - 1);
        }
        return true;
    }

    // while
    if (command.substr(0, 5) == "while")
    {
        if (commands.nextCommand() != "{")
        {
            throw runtime_error("blocks should start with \'{\'");
        }
        if (core.isCurrentZero())
        {
            int blockEnd = commands.findBlockEnd();
            commands.jumpToCommand(blockEnd);
        }
        else
        {
            callStack.push_back(commands.getCurrentAddress() - 1);
        }
        return true;
    }

    // for
    if (command.substr(0, 3) == "for")
    {
        if (commands.nextCommand() != "{")
        {
            throw runtime_error("blocks should start with \'{\'");
        }
        if (command.substr(4, command.length() - 4) == "0")
        {
            int blockEnd = commands.findBlockEnd();
            commands.jumpToCommand(blockEnd);
        }
        else
        {
            callStack.push_back(commands.getCurrentAddress() - 1);
        }
        return true;
    }

    // }
    if (command.substr(0, 1) == "}")
    {
        if (callStack.empty())
        {
            throw runtime_error("there were no block openings before");
        }
        int lastCall = callStack.back();
        callStack.pop_back();
        int prevAdress = commands.getCurrentAddress();
        commands.jumpToCommand(lastCall);
        if (commands.getCurrentCommand().substr(0, 2) == "if")
        {
            commands.jumpToCommand(prevAdress);
            return true;
        }
        if (commands.getCurrentCommand().substr(0, 5) == "while")
        {
            return false;
        }
        if (commands.getCurrentCommand().substr(0, 3) == "for")
        {
            commands.decrementForNumber();
            return false;
        }
    }

    // plus
    if (command.substr(0, 4) == "plus")
    {
        if (command.length() != 4)
        {
            int amount = stoi(command.substr(5, command.length() - 5));
            core.plus(amount);
            return true;
        }
        core.plus();
        return true;
    }

    // minus
    if (command.substr(0, 5) == "minus")
    {
        if (command.length() != 5)
        {
            int amount = stoi(command.substr(6, command.length() - 6));
            core.minus(amount);
            return true;
        }
        core.minus();
        return true;
    }

    // right
    if (command.substr(0, 5) == "right")
    {
        if (command.length() != 5)
        {
            int amount = stoi(command.substr(6, command.length() - 6));
            core.right(amount);
            return true;
        }
        core.right();
        return true;
    }

    // left
    if (command.substr(0, 4) == "left")
    {
        if (command.length() != 4)
        {
            int amount = stoi(command.substr(5, command.length() - 5));
            core.left(amount);
            return true;
        }
        core.left();
        return true;
    }

    // print
    if (command.substr(0, 5) == "print")
    {
        if (command.length() != 5)
        {
            int amount = stoi(command.substr(6, command.length() - 6));
            core.print(cout, amount);
            return true;
        }
        core.print(cout);
        return true;
    }

    // input
    if (command.substr(0, 5) == "input")
    {
        if (command.length() != 5)
        {
            int amount = stoi(command.substr(6, command.length() - 6));
            core.input(cin, amount);
            return true;
        }
        core.input(cin);
        return true;
    }
    throw runtime_error("invalid command");
}
