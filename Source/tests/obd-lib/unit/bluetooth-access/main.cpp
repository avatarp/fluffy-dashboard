#include "bluetooth-obd-access-test.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int testsResults = RUN_ALL_TESTS();
    return testsResults;
}
