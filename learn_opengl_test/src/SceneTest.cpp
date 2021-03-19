#include <gtest/gtest.h>
#include "061_Camera.h"

TEST(Scence061, Basics) {
    int success = LearnOpenGL::flyThroughScene();
    EXPECT_EQ(success, 0);
}
