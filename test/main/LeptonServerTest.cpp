#include <io/FileSystemImageStream.h>
#include <types/Image8bit.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include <comm/TCPImageServer.h>
#include <io/TCPImageStream.h>

/**
 * This tests the ability to connect to a separate server streaming Lepton images.
 *
 * Requires that a TCPImageServer be running at the endpoint specified.
 *  Whenever it receives a request, the server at that endpoint replies
 *  with an image. The client side then displays its received images one
 *  by one, waiting for keyboard input from the user to show the
 *  next image.
 *
 * Note that the images are very small (60 by 80 pixels), so they might be hard
 *  to spot on your screen.
 */
int main() {
    TCPImageStream client("10.42.0.10", "5555");

    SimpleRescaler rescaler;
    Image8bit displayed(client.getImageHeight(), client.getImageWidth());

    while (client.hasNext()) {
        rescaler.scale16bitTo8bit(client.nextImage(), displayed);
        cv::imshow("LeptonServer Test", displayed);
        cv::waitKey(0);
    }
}
