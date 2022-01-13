#include <gtest/gtest.h>

#include "version.h"

TEST(version, basic_test) {
    ASSERT_NE(version(), -1);
}
