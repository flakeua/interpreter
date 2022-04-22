//
// Created by Dima on 24.12.2021.
//
#include <iostream>
#include "gmock/gmock.h"
#include "vector"

#include "Commands.h"

using namespace std;
using namespace ::testing;

TEST(CommandsTests, addCommands)
{
    Commands commands;
    ASSERT_THAT(commands.getCommands(), ElementsAre());
    commands.addCommands("  a  \n ad asa   \n sf");
    ASSERT_THAT(commands.getCommands(), ElementsAre("a", "ad asa", "sf"));
    ASSERT_EQ(commands.getCurrentCommand(), "a");
}

TEST(CommandsTests, doubleSpacesTabs)
{
    Commands commands;
    commands.addCommands("\n\n\n aaf  sfd \nads    sdf   \n ad        asahh\n}\n");
    ASSERT_THAT(commands.getCommands(), ElementsAre("aaf sfd", "ads sdf", "ad asahh", "}"));
    ASSERT_EQ(commands.getCurrentCommand(), "aaf sfd");
}

TEST(CommandsTests, nextCommand)
{
    Commands commands;
    commands.addCommands(" aaf  sfd \n ads    sdf   \n ad        asahh\n}\n");
    ASSERT_EQ(commands.nextCommand(), "ads sdf");
    ASSERT_EQ(commands.nextCommand(), "ad asahh");
    ASSERT_EQ(commands.getCurrentCommand(), "ad asahh");
    ASSERT_EQ(commands.nextCommand(), "}");
    ASSERT_THROW(commands.nextCommand(), out_of_range);
}

TEST(CommandsTests, outOfRange)
{
    Commands commands;
    ASSERT_THROW(commands.nextCommand(), out_of_range);
    Commands commands2;
    ASSERT_THROW(commands2.getCurrentCommand(), out_of_range);
}

TEST(CommandsTests, jumpToCommand)
{
    Commands commands;
    commands.addCommands("agae\n  { \naaf  sfd \n ads    sdf   \n ad        asahh\n}\n age\n{\n}\n{");
    ASSERT_EQ(commands.getCurrentCommand(), "agae");
    commands.jumpToCommand(2);
    ASSERT_EQ(commands.getCurrentCommand(), "aaf sfd");
    ASSERT_EQ(commands.nextCommand(), "ads sdf");
    ASSERT_EQ(commands.nextCommand(), "ad asahh");
    commands.jumpToCommand(5);
    ASSERT_EQ(commands.getCurrentCommand(), "}");
    commands.jumpToCommand(0);
    ASSERT_EQ(commands.getCurrentCommand(), "agae");
}

TEST(CommandsTests, jumpToCommandOutOfRange)
{
    Commands commands;
    commands.addCommands("agae\n  { \naaf  sfd \n ads    sdf   \n ad        asahh\n}\n age\n{\n}\n{");
    ASSERT_THROW(commands.jumpToCommand(-4), out_of_range);
    Commands commands2;
    commands2.addCommands("agae\n  { \naaf  sfd \n ads    sdf   \n ad        asahh\n}\n age\n{\n}\n{");
    ASSERT_THROW(commands2.jumpToCommand(10), out_of_range);
}

TEST(CommandsTests, findBlockEnd)
{
    Commands commands;
    commands.addCommands("agae\n  { \naaf  sfd \n ads    sdf   \n ad        asahh\n}\n age\n{\n}\n{");
    commands.nextCommand();
    ASSERT_EQ(commands.findBlockEnd(), 5);
    commands.jumpToCommand(5);
    commands.nextCommand();
    ASSERT_THROW(commands.findBlockEnd(), invalid_argument);
}

TEST(CommandsTests, findBlockEnd2)
{
    Commands commands;
    commands.addCommands("agae\n  { \naaf  sfd \n ads    sdf   \n ad        asahh\n}\n age\n{\n}\n{");
    commands.jumpToCommand(7);
    ASSERT_EQ(commands.findBlockEnd(), 8);
    commands.jumpToCommand(9);
    ASSERT_THROW(commands.findBlockEnd(), length_error);
}

TEST(CommandsTests, EmptyExeptions)
{
    Commands commands;
    ASSERT_THROW(commands.findBlockEnd(), invalid_argument);
    Commands commands2;
    ASSERT_THROW(commands2.jumpToCommand(2), out_of_range);
    Commands commands3;
    ASSERT_THROW(commands3.decrementForNumber(), out_of_range);
}

TEST(CommandsTests, decrementForNumber)
{
    Commands commands;
    commands.addCommands("ageaga \nfor 5\n  { \n}");
    commands.nextCommand();
    ASSERT_THAT(commands.getCommands(), ElementsAre("ageaga", "for 5", "{", "}"));
    commands.decrementForNumber();
    ASSERT_THAT(commands.getCommands(), ElementsAre("ageaga", "for 4", "{", "}"));
    commands.decrementForNumber();
    ASSERT_THAT(commands.getCommands(), ElementsAre("ageaga", "for 3", "{", "}"));
    commands.decrementForNumber();
    ASSERT_THAT(commands.getCommands(), ElementsAre("ageaga", "for 2", "{", "}"));
    commands.decrementForNumber();
    ASSERT_THAT(commands.getCommands(), ElementsAre("ageaga", "for 1", "{", "}"));
    commands.decrementForNumber();
    ASSERT_THAT(commands.getCommands(), ElementsAre("ageaga", "for 0", "{", "}"));
    ASSERT_THROW(commands.decrementForNumber(), out_of_range);
}

TEST(CommandsTests, decrementForNumberInvalidArgument)
{
    Commands commands;
    commands.addCommands("for b\n3");
    ASSERT_THROW(commands.decrementForNumber(), invalid_argument);
    Commands commands2;
    commands2.addCommands("agewa \n asdg");
    ASSERT_THROW(commands2.decrementForNumber(), invalid_argument);
}