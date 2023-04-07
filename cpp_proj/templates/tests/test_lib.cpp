#include <gtest/gtest.h>

#include "{{lib.specs.dir}}/{{lib.specs.filename}}.h"

TEST(Test{{lib.specs.dir|capitalize}}, ReturnTrueReturnsTrue)
{
    {{lib.specs.dir}}::{{lib.specs.class}} lib;

    auto ret = lib.ReturnTrue();
    EXPECT_EQ(ret, true);	
}
