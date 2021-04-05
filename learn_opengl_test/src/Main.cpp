#include "gtest/gtest.h"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(filter) = "Experiments.ImageViewer";
    return RUN_ALL_TESTS();
}