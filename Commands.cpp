//
// Created by Dima on 23.12.2021.
//

#include "string"
#include "Commands.h"

using namespace std;

string deleteFirstLastWhiteSpaces(string current)
{
    int i = 0;
    for (; i < current.length(); i++)
    {
        if (current[i] != ' ')
        {
            break;
        }
    }
    int j = current.length() - 1;
    for (; j > 0; j--)
    {
        if (current[j] != ' ')
        {
            break;
        }
    }
    current = current.substr(i, j - i + 1);
    return current;
}

string deleteWhiteSpacesBeetweenWords(string current)
{
    string res = "";
    string buff = "x";
    for (char c : current)
    {
        if (buff.back() != ' ' && c == ' ')
        {
            res.push_back(' ');
        }
        buff.push_back(c);
        if (c != ' ')
        {
            res.push_back(c);
        }
    }
    return res;
}
string stringToLower(string str)
{
    string res = "";
    for (char c : str)
    {
        res += (char)tolower(c);
    }
    return res;
}

void Commands::addCommands(string commands0)
{
    string line = "";
    for (auto c : commands0)
    {
        if (c == '\n')
        {
            line = stringToLower(line);
            line = deleteFirstLastWhiteSpaces(line);
            line = deleteWhiteSpacesBeetweenWords(line);
            if (!line.empty())
                commands.push_back(line);
            line = "";
            continue;
        }
        line += c;
    }
    if (!line.empty())
    {
        line = stringToLower(line);
        line = deleteFirstLastWhiteSpaces(line);
        line = deleteWhiteSpacesBeetweenWords(line);
        if (!line.empty())
            commands.push_back(line);
    }
}

void Commands::jumpToCommand(int address)
{
    if (address < 0 || address >= commands.size())
    {
        throw out_of_range("command address out of range");
    }
    current_address = address;
}

string Commands::nextCommand()
{
    if (current_address + 1 >= commands.size())
    {
        throw out_of_range("next is out of range");
    }
    current_address++;
    return commands[current_address];
}

int Commands::findBlockEnd()
{
    if (commands.empty())
    {
        throw invalid_argument("empty commands");
    }
    if (commands[current_address] != "{")
    {
        throw invalid_argument("current is not \'{\'");
    }
    int balance = 1;
    for (int i = current_address + 1; i < commands.size(); i++)
    {
        if (commands[i] == "{")
        {
            balance++;
        }
        if (commands[i] == "}")
        {
            balance--;
        }
        if (balance == 0)
        {
            return i;
        }
    }
    throw length_error("there is no pairing bracket");
}

void Commands::decrementForNumber()
{
    string current = getCurrentCommand();
    if (current.substr(0, 3) != "for")
    {
        throw invalid_argument("current command is not for");
    }
    int argument = stoi(current.substr(4, current.length() - 4));
    if (argument <= 0)
    {
        throw out_of_range("for is already zero");
    }
    commands[current_address] = "for " + to_string(argument - 1);
}

string Commands::getCurrentCommand()
{
    if (commands.empty())
    {
        throw out_of_range("there are no commands");
    }
    return commands[current_address];
}
