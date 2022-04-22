#include <iostream>
#include "gmock/gmock.h"
#include "Core.h"
#include "Reader.h"
#include "Commands.h"

using namespace std;

const bool isTesting = true;

void usageError()
{
    cout << "Usage: interpreter [-s] [size] [filename]";
}

int main(int argc, char **argv)
{
    if (isTesting)
    {
        testing::InitGoogleMock(&argc, argv);
        return RUN_ALL_TESTS();
    }

    string fname = "";
    int size = 30000;
    if (argc > 1)
    {
        if (argc == 2)
        {
            fname = argv[1];
            if (fname == "")
            {
                usageError();
                return 1;
            }
        }
        else if (argc == 3 && string(argv[1]) == "-s")
        {
            size = stoi(argv[2]);
        }
        else if (argc == 4 && string(argv[1]) == "-s")
        {
            size = stoi(argv[2]);
            fname = argv[3];
            if (fname == "")
            {
                usageError();
                return 1;
            }
        }
        else
        {
            usageError();
            return 1;
        }
    }
    if (size == 0)
    {
        usageError();
        return 1;
    }
    Core core(size);
    Commands commands;
    Reader reader(core, commands);
    if (fname == "")
    {
        reader.interactiveMode();
        return 0;
    }
    reader.interpretFile(fname);
    return 0;
}
