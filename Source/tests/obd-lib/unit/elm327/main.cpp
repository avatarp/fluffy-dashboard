#include "command-repo-test.h"
#include "decoders-test.h"
#include "live-data-test.h"
#include "parser-test.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int testsResults = RUN_ALL_TESTS();
    return testsResults;
}
