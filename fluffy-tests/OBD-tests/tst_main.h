#ifndef TST_MAIN_H
#define TST_MAIN_H

#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(FluffyTest, main)
{
    EXPECT_EQ(1, 1);
    ASSERT_EQ(1,1);
}

TEST(Fluffy,main)
{
    ASSERT_EQ(1+1,2);
}
#endif // TST_MAIN_H
