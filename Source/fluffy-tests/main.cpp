#include "decorders.h"
#include "usb-obd-access.h"
#include "bluetooth-obd-access.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int TestsResults = RUN_ALL_TESTS();
    CleanupEnvironment();
    return TestsResults;
}
