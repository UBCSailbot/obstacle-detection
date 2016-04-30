#include <zmq.hpp>
#include <types/CameraData.h>
#include <io/CameraDataDeserializer.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <comm/TCPCameraCommsSub.h>
#include <imageProc/rescale/SimpleRescaler.h>

#define APPNAME "TCPCameraCommsTest"

using namespace std;

/**
 * Spins up a subscriber thread that listens
 *  for ZeroMQ messages coming from the specified port
 *  at the specified IP address.
 * At the same time, the main thread makes requests to the
 *  subscriber thread for images every requestRateMs milliseconds.
 *  (A value of 0 makes the program wait until a keypress
 *  before showing the next frame.)
 * The subscriber thread complies whenever it has any new
 *  images, sending them back to the main thread,
 *  which then displays the images as soon as it receives
 *  them. If the main thread makes requests more
 *  frequently than the subscriber receives new images,
 *  the main thread ends up waiting until the subscriber
 *  has received new images.
 *
 * Note that for this function to do anything requires another
 *  process sending properly formatted ZeroMQ messages from
 *  the corresponding IP address and port number.
 * For example, the executable compiled from CameraEnclosureServer.cpp
 *  is capable of fulfilling this contract.
 */
void run(string pubIPaddress, string pubPortNumber, int requestRateMs, bool debug) {
    zmq::context_t context;
    zmq::socket_t pairSocket(context, ZMQ_PAIR);

    string inprocAddress = "inproc://" + TCPCameraCommsSub::ENDPOINT_NAME;
    pairSocket.bind(inprocAddress.c_str());

    // Spins up a separate subscriber thread that receives and stores
    //  the latest images sent by the camera server publisher
    TCPCameraCommsSub sub(context, pubIPaddress, pubPortNumber);

    zmq::message_t request;
    zmq::message_t reply;

    SimpleRescaler rescaler;

    while (true) {
        pairSocket.send(request);
        pairSocket.recv(&reply);

        vector<CameraData> dataVector = CameraDataDeserializer::deserializeFromZmq(reply);

        if (debug) {
            cout << "Received data from " << dataVector.size() << " cameras!" << endl;
        }

        int imageNumber = 0;
        string windowNameTemplate = "Image ";

        for (CameraData data : dataVector) {
            if (data.status == OK) {
                Image16bit img = data.frame;
                Image8bit display(img.rows, img.cols);
                rescaler.scale16bitTo8bit(img, display);
                
                imshow(windowNameTemplate + to_string(imageNumber), display);
                imageNumber++;
            }
            else {
                cout << "Image status was " << data.status << endl;
            }
        }

        cv::waitKey(requestRateMs);
    }
}

int main(int argc, char** argv) {

    if (argc < 4) {
        cout << endl;
        cout << "Usage: " << APPNAME << " [pub_IPv4_address] "
                     "[pub_port#] [display_framerate_ms]" << endl;
        cout << endl;
        cout << "e.g. ./" << APPNAME << " 10.8.0.4 5555 100" << endl;
        cout << endl;
         cout << "Receives images being published from a ZeroMQ "
                         "instance at [pub_IPv4_address] on port "
                         "[pub_port#] and displays them at a framerate "
                         "of [display_framerate_ms]. Read the documentation "
                         "in the source code file from which this binary "
                         "was compiled for a full explanation "
                         "of how this works." << endl;
        exit(0);
    }

    bool debug = false;
    if (argc == 5) {
        debug = true;
    }

    string address(argv[1]), port(argv[2]);
    int displayRateMs = stoi(argv[3]);

    run(address, port, displayRateMs, debug);


}
