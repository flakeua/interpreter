//
// Created by Dima on 23.12.2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Core.h"

using namespace std;

void checkNegative(int n)
{
    if (n <= 0)
    {
        throw invalid_argument("Negative argument or zero");
    }
}

void Core::left(int n)
{
    checkNegative(n);
    if (current - n < 0)
    {
        throw out_of_range("n is too high");
    }
    current -= n;
}

void Core::right(int n)
{
    checkNegative(n);
    if (current + n >= size)
    {
        throw out_of_range("n is too high");
    }
    current += n;
}

void Core::plus(int n)
{
    checkNegative(n);
    if (memory[current] + n > 255)
    {
        throw out_of_range("n is too high");
    }
    memory[current] += n;
}

void Core::minus(int n)
{
    checkNegative(n);
    if (memory[current] - n < 0)
    {
        throw out_of_range("n is too high");
    }
    memory[current] -= n;
}

void Core::print(ostream &output, int n)
{
    checkNegative(n);
    if (current + n - 1 >= size)
    {
        throw out_of_range("printing too many elements");
    }
    string res = "";
    for (int i = 0; i < n; i++)
    {
        res += memory[current++];
    }
    current--;
    output << res;
}

void Core::input(istream &input, int n)
{
    checkNegative(n);
    int i = 0;
    int curr = current;
    while (i < n)
    {
        string res;
        getline(input, res);
        for (auto c : res)
        {
            if (curr == size)
            {
                throw out_of_range("input is too long");
            }
            memory[curr++] = c;
        }
        i++;
    }
}
