#include <gtest/gtest.h>

#include "tools/ImageViewerApp.h"

TEST(Tools, ImageViewer) {
    int success = runImageViewer();
    EXPECT_EQ(success, 0);
}
