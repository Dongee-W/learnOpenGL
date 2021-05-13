#include <gtest/gtest.h>
#include "010_MinimalCode.h"
#include "030_Texture.h"
#include "061_CameraModule.h"
#include "070_Mesh.h"

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

TEST(Scene070, Mesh) {
    testtest();
}
