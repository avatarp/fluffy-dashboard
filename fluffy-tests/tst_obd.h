#ifndef TST_OBD_H
#define TST_OBD_H

#include <gtest/gtest.h>
#include "../obd.h"

using namespace testing;

TEST(fluffy_tests, obd)
{
    EXPECT_EQ(1, 1);
}

TEST(isConnected, obd)
{
    obd2Interface obd;
    EXPECT_FALSE(obd.isConnected());
}

#endif // TST_OBD_H
