#include <gtest/gtest.h>
#include "010_MinimalCode.h"
#include "030_Texture.h"
#include "061_CameraModule.h"
#include "070_Light.h"
#include "080_Model.h"
#include "081_WarhoundAnimation.h"

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

TEST(Scene070, Lighting) {
    demoLightingScene();
}

TEST(Scene080, Model) {
    demoBackpackScene();
}
TEST(Scene081, Warhound) {
    animateWarhound();
}
