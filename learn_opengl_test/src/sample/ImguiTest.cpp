#include <gtest/gtest.h>

#include "sample/ImguiDemo.h"

TEST(Sample, Imgui) {
    int success = imguiDemo();
    EXPECT_EQ(success, 0);
}
