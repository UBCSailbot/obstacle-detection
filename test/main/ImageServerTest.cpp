#include <Resources.h>
#include <io/Paths.h>
#include <io/FileSystemImageStream.h>
#include <types/Image8bit.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include <comm/TCPImageServer.h>
#include <io/TCPImageStream.h>

/**
 * This test pairs a TCPImageServer with a TCPImageStream to test their interaction
 *  over a network.
 * The TCPImageServer is fed a FileSystemImageStream that goes through
 *  the images in the resources/img/16bit directory of this project, which it sends
 *  to TCPImageStream whenever it receives a request. The client side then displays
 *  its received images one by one, waiting for keyboard input from the user to show the
 *  next image.
 *
 * Note that the images are very small (60 by 80 pixels), so they might be hard
 *  to spot on your screen.
 */
int main() {
    std::string inputFrameDir = Paths::join(Resources::RESOURCE_DIR, "img/16bit");
    FileSystemImageStream fsStream(inputFrameDir, "*.png");

    TCPImageServer server(fsStream, "*", "5555");
    TCPImageStream client("localhost", "5555");

    SimpleRescaler rescaler;
    Image8bit displayed(fsStream.getImageHeight(), fsStream.getImageWidth());

    // TODO: Enhance client/server messaging so that we can use while(client.hasNext())
//    while(client.hasNext()) {
    for (int i = 0; i < 3; i++) {
        rescaler.scale16bitTo8bit(client.nextImage(), displayed);
        cv::imshow("FileSystemImageStream Test", displayed);
        cv::waitKey(0);
    }

}
