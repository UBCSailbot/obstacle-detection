//
// Created by paul on 09/02/16.
//

#include <Resources.h>
#include <io/Paths.h>
#include <io/FileSystemImageStream.h>
#include <types/Image8bit.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include <comm/ImageServer.h>
#include <io/ClientImageStream.h>

/**
 * This test pairs an ImageServer with a ClientImageStream to test their interaction
 *  over a network.
 * The ImageServer is fed a FileSystemImageStream that goes through
 *  the images in the resources/img/16bit directory of this project, which it sends
 *  to ClientImageStream whenever it receives a request. The client side then displays
 *  its received images one by one, waiting for keyboard input from the user to show the
 *  next image.
 *
 * Note that the images are very small (60 by 80 pixels), so they might be hard
 *  to spot on your screen.
 */
int main() {
    std::string inputFrameDir = Paths::join(Resources::RESOURCE_DIR, "img/16bit");
    FileSystemImageStream fsStream(inputFrameDir, "*.png");

    ImageServer server(fsStream, "tcp://*:5555");
    ClientImageStream client("tcp://localhost:5555");

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