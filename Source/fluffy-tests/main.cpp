#include "elm327/decorders.h"
#include "elm327/elm327-live-data.h"
#include "usb-obd-access.h"
#include "bluetooth-obd-access.h"
#include "elm327/parser.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int TestsResults = RUN_ALL_TESTS();
    return TestsResults;
}
