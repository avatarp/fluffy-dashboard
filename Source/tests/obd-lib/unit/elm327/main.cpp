#include "command-repo-test.h"
#include "live-data-test.h"
#include "parser-test.h"
#include "response-test.h"
#include "dtc-handler-test.h"

#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
