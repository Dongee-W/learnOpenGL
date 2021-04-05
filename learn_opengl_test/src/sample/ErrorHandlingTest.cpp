#include <gtest/gtest.h>

#include "sample/ErrorHandling.h"

TEST(Sample, ErrorHandling) {
    int success = demoErrorHandling();
    EXPECT_EQ(success, 0);
}