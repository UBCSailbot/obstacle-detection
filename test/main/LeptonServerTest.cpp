#include <io/FileSystemImageStream.h>
#include <types/Image8bit.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include <comm/TCPImageServer.h>
#include <io/TCPImageStream.h>
#include <opencv2/imgproc/imgproc.hpp>

#define APPNAME "leptonServerTest"

/**
 * This tests the ability to connect to a separate server streaming Lepton images.
 *
 * Requires that a TCPImageServer be running at the endpoint specified.
 *  Whenever it receives a request, the server at that endpoint replies
 *  with an image. The client side then displays its received images one
 *  by one, waiting for keyboard input from the user to show the
 *  next image.
 */
int main(int argc, char** argv) {

#ifdef DEBUG
    TCPImageStream client("localhost", "5555");
#else
    if (argc < 2) {
        std::cout << "Usage: " << APPNAME << " [IPv4_address] [port#]" << std::endl;
        exit(0);
    }
    std::string address(argv[1]), port(argv[2]);

    TCPImageStream client(address, port);
#endif

    SimpleRescaler rescaler;
    Image8bit rescaled(client.getImageHeight(), client.getImageWidth());
    Image8bit displayed;

    while (client.hasNext()) {
        rescaler.scale16bitTo8bit(client.nextImage(), rescaled);
        cv::resize(rescaled, displayed, cv::Size(800, 600), cv::INTER_NEAREST);
        cv::imshow("LeptonServer Test", displayed);
        cv::waitKey(100);
    }
}
