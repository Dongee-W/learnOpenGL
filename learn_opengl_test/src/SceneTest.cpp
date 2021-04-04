#include <gtest/gtest.h>
#include "010_MinimalCode.h"
#include "030_Texture.h"
#include "061_CameraModule.h"

TEST(Scene010, MinimalCode) {
    int success = MinimalCode::demoMinimalOpenGL();
}

TEST(Scene030, Texture) {
    int success = demoTexture();
    EXPECT_EQ(success, 0);
}

TEST(Scene061, Basics) {
    int success = LearnOpenGL::demoFlyThroughScene();
    EXPECT_EQ(success, 0);
}
