#include <gtest/gtest.h>

TEST(TestBasic, TestSuccess)
{
    EXPECT_EQ(1000, 1000);	
}

TEST(TestBasic, TestFail)
{
    EXPECT_EQ(1000, 1001);	
}
