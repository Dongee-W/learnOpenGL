#include <gtest/gtest.h>

#include "sample/OpenGLClasses.h"

TEST(Sample, OpenGLClasses) {
    int success = demoOpenGLClasses();
    EXPECT_EQ(success, 0);
}

TEST(Sample, OpenGLClassesMesh) {
    int success = demoOpenGLClassesMesh();
    EXPECT_EQ(success, 0);
}