#include <gtest/gtest.h>
#include "03_Texture.h"
#include "061_Camera.h"

TEST(Scene03, Texture) {
    int success = demoTexture();
    EXPECT_EQ(success, 0);
}

TEST(Scene061, Basics) {
    int success = LearnOpenGL::demoFlyThroughScene();
    EXPECT_EQ(success, 0);
}
