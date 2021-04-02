#include <gtest/gtest.h>

#include "experiments/ImageViewer.h"

TEST(Experiments, Image2D) {
    int success = ImageViewer::runImageViewer();
    EXPECT_EQ(success, 0);
}
