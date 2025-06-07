#ifndef COMMAND_REPO_TEST_H_
#define COMMAND_REPO_TEST_H_

#include "elm327-command-repository.hpp"
#include <bitset>
#include <optional>

#include <gtest/gtest.h>

using namespace testing;

class elm327CommandRepo : public ::testing::Test {
protected:
    Elm327CommandRepository repo {};
};

TEST_F(elm327CommandRepo, getCommandByPidInvalid)
{
    constexpr int invalidCommandPid { 255 };
    EXPECT_EQ(repo.getCommandByPid(ObdCommandPid { invalidCommandPid }), std::string {});
}

TEST_F(elm327CommandRepo, getCommandByPidS01)
{
    constexpr int commandPid01Max { 64 };
    for (int i = 0; i < commandPid01Max; i++) {
        std::stringstream expectedString;
        if (i < 16)
            expectedString << "010" << std::uppercase << std::hex << i << "\r";
        else
            expectedString << "01" << std::uppercase << std::hex << i << "\r";
        EXPECT_EQ(repo.getCommandByPid(ObdCommandPid(i)), expectedString.str());
    }
}

TEST_F(elm327CommandRepo, getCommandByPidS03)
{
    constexpr int commandPid03Dtc { static_cast<int>(ObdCommandPid::S03) };
    EXPECT_EQ(repo.getCommandByPid(ObdCommandPid { commandPid03Dtc }), std::string { "03\r" });
}

#endif // COMMAND_REPO_TEST_H_