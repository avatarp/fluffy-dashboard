#include "elm327/decoders.h"
#include "elm327/elm327-live-data.h"
#include "elm327/parser.h"
#include "usb-obd-access.h"
#include "bluetooth-obd-access.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int TestsResults = RUN_ALL_TESTS();
    return TestsResults;
}
