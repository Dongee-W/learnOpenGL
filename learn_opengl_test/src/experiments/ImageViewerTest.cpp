#include <gtest/gtest.h>

#include "experiments/ImageViewer.h"

TEST(Experiments, ImageViewer) {
    int success = runImageViewer();
    EXPECT_EQ(success, 0);
}
