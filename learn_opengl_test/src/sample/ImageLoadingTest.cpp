#include <gtest/gtest.h>

#include "sample/ImageLoading.h"

TEST(Sample, ImageLoading) {
    int success = demoImageLoading();
    EXPECT_EQ(success, 0);
}
