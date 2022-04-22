//
// Created by Dima on 17.12.2021.
//

#ifndef INTERPRETER_CORE_H
#define INTERPRETER_CORE_H

#include <vector>

using namespace std;

class Core
{
    int size;
    vector<unsigned char> memory;
    int current = 0;

public:
    Core(int array_size) : size(array_size), memory(array_size)
    {
        fill(memory.begin(), memory.end(), 0);
    }

    bool isCurrentZero() const { return memory[current] == 0; };

    vector<unsigned char> getArray() { return memory; }

    void left(int n = 1);

    void right(int n = 1);

    void plus(int n = 1);

    void minus(int n = 1);

    void print(ostream &output, int n = 1);

    void input(istream &input, int n = 1);

private:
};

#endif // INTERPRETER_CORE_H
