//
// Created by paul on 09/02/16.
//

#include <io/FileSystemImageStream.h>
#include <Resources.h>
#include <imageProc/rescale/SimpleRescaler.h>

/**
 * This test builds a FileSystemImageStream that goes through all
 *  the images in the resources/img/16bit directory of this project and displays
 *  them one by one, waiting for keyboard input from the user to show the
 *  next image.
 *
 * Note that the images are very small (60 by 80 pixels), so they might be hard
 *  to spot on your screen.
 */
int main() {
    std::string inputFrameDir = Paths::join(Resources::RESOURCE_DIR, "img/16bit");
    FileSystemImageStream fsStream(inputFrameDir, "*.png");
    SimpleRescaler rescaler;
    Image8bit displayed(fsStream.getImageHeight(), fsStream.getImageWidth());

    while(fsStream.hasNext()) {
        rescaler.scale16bitTo8bit(fsStream.nextImage(), displayed);
        cv::imshow("FileSystemImageStream Test", displayed);
        cv::waitKey(0);
    }
}