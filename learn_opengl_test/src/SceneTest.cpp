#include <gtest/gtest.h>
#include "010_MinimalCode.h"
#include "030_Texture.h"
#include "061_CameraModule.h"

TEST(Scene010, MinimalCode) {
    int success = demoMinimalOpenGL();
}

TEST(Scene030, Texture) {
    int success = demoTexture();
    EXPECT_EQ(success, 0);
}

TEST(Scene061, Basics) {
    int success = LearnOpenGL::demoFlyThroughScene();
    EXPECT_EQ(success, 0);
}

TEST(HELLO, random) {
    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };

    std::cout << sizeof(vertices) << std::endl;
}
