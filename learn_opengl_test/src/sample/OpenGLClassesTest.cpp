#include <gtest/gtest.h>

#include "sample/OpenGLClasses.h"

TEST(Sample, OpenGLClasses) {
    int success = demoOpenGLClasses();
    EXPECT_EQ(success, 0);
}