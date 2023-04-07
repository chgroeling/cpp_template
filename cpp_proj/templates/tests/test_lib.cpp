#include <gtest/gtest.h>

#include "{{LIB.DIR}}/{{LIB.FILENAME}}.h"

TEST(Test{{LIB.DIR|capitalize}}, ReturnTrueReturnsTrue)
{
    {{LIB.DIR}}::{{LIB.CLASS}} lib;

    auto ret = lib.ReturnTrue();
    EXPECT_EQ(ret, true);	
}
