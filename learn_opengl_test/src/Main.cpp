#include "gtest/gtest.h"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(filter) = "Scene070.Mesh";
    return RUN_ALL_TESTS();
}