//
// Created by Dima on 17.12.2021.
//

#include <iostream>
#include <fstream>
#include "gmock/gmock.h"
#include "vector"

#include "Core.h"

using namespace std;
using namespace ::testing;

TEST(CoreTests, negatives)
{
    Core core(1);
    ASSERT_THROW(core.right(-1), invalid_argument);
    ASSERT_THROW(core.left(-2), invalid_argument);
    ASSERT_THROW(core.plus(-3), invalid_argument);
    ASSERT_THROW(core.minus(-4), invalid_argument);
}

TEST(CoreTests, memoryOutOfRange)
{
    Core core(4);
    ASSERT_NO_THROW(core.right(3));
    ASSERT_THROW(core.right(), out_of_range);
    Core core2(4);
    ASSERT_THROW(core2.left(), out_of_range);
}

TEST(CoreTests, plus)
{
    Core core(3);
    core.plus();
    core.right();
    core.plus(2);
    core.right();
    core.plus(3);
    ASSERT_THAT(core.getArray(), ElementsAre(1, 2, 3));
}

TEST(CoreTests, minus)
{
    Core core(10);
    core.right(4);
    core.plus(10);
    core.left(2);
    core.plus();
    core.right(5);
    core.plus(7);
    core.left(3);
    core.minus();
    core.right();
    core.plus(255);
    core.right(2);
    core.minus(4);
    ASSERT_THAT(core.getArray(), ElementsAre(0, 0, 1, 0, 9, 255, 0, 3, 0, 0));
}

TEST(CoreTests, plusOutOfRange)
{
    Core core(1);
    ASSERT_NO_THROW(core.plus(255));
    ASSERT_THROW(core.plus(), out_of_range);
    Core core2(2);
    ASSERT_THROW(core2.plus(242322), out_of_range);
}

TEST(CoreTests, minusOutOfRange)
{
    Core core(1);
    ASSERT_THROW(core.minus(), out_of_range);
    Core core2(2);
    core2.plus(5);
    ASSERT_THROW(core2.minus(23523), out_of_range);
}

TEST(CoreTests, isCurrentZero)
{
    Core core(10);
    core.plus();
    ASSERT_FALSE(core.isCurrentZero());
    core.right();
    ASSERT_TRUE(core.isCurrentZero());
    core.plus(5);
    ASSERT_FALSE(core.isCurrentZero());
    core.minus(5);
    ASSERT_TRUE(core.isCurrentZero());
    core.right(5);
    core.plus(5);
    core.left(3);
    ASSERT_TRUE(core.isCurrentZero());
    core.right(3);
    ASSERT_FALSE(core.isCurrentZero());
}

TEST(CoreTests, input)
{
    Core core(30);
    core.right();
    ifstream input("input.txt");
    core.input(input);
    ASSERT_THAT(
        core.getArray(), ElementsAre(
                             0, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r',
                             'l', 'd', 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    input.close();
    input.open("input.txt");
    core.input(input, 3);
    ASSERT_THAT(
        core.getArray(), ElementsAre(
                             0, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r',
                             'l', 'd', 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o',
                             'r', 'l', 'd', '1', '2', '3', '4', '5', 0, 0));
    input.close();
}

TEST(CoreTests, output)
{
    Core core(11);
    core.plus('h');
    core.right();
    core.plus('e');
    core.right();
    core.plus('l');
    core.right();
    core.plus('l');
    core.right();
    core.plus('o');
    core.left(4);
    ostringstream out;
    core.print(out);
    ASSERT_EQ(out.str(), "h");
    out.str("");
    core.print(out, 5);
    core.print(out);
    ASSERT_EQ(out.str(), "helloo");
}

TEST(CoreTests, outputOutOfRange)
{
    Core core(1);
    ostringstream out;
    ASSERT_THROW(core.print(out, 2), out_of_range);
}

TEST(CoreTests, inputOutOfRange)
{
    Core core(1);
    ifstream input;
    input.open("input.txt", ifstream::in);
    ASSERT_THROW(core.input(input), out_of_range);
    input.close();
}

TEST(CoreTests, inputOutputNegative)
{
    Core core(20);
    ostringstream out;
    ASSERT_THROW(core.print(out, -2), invalid_argument);
    ifstream input;
    input.open("input.txt", ifstream::in);
    ASSERT_THROW(core.input(input, -4), invalid_argument);
    input.close();
}