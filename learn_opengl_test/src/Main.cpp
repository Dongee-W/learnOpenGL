#include "gtest/gtest.h"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(filter) = "Scene081.Joint";
    //testing::GTEST_FLAG(filter) = "Sample.OpenGLClassesMesh";
    
    return RUN_ALL_TESTS();
}