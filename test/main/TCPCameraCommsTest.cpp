#include <zmq.hpp>
#include <types/CameraData.h>
#include <io/CameraDataDeserializer.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <comm/TCPCameraCommsSub.h>
#include <imageProc/rescale/SimpleRescaler.h>

int main() {

    zmq::context_t context;
    zmq::socket_t pairSocket(context, ZMQ_PAIR);

    std::string inprocAddress = "inproc://" + TCPCameraCommsSub::ENDPOINT_NAME;
    pairSocket.bind(inprocAddress.c_str());

    TCPCameraCommsSub sub(context, "localhost", "5555");

    zmq::message_t request;
    zmq::message_t reply;

    SimpleRescaler rescaler;


    while (true) {
        pairSocket.send(request);
        pairSocket.recv(&reply);

        std::vector<CameraData> dataVector = CameraDataDeserializer::deserializeFromZmq(reply);

        std::cout << "Received data from " << dataVector.size() << " cameras!" << std::endl;

        for (CameraData data : dataVector) {
            if (data.status == OK) {
                Image16bit img = data.frame;
                Image8bit display(img.rows, img.cols);
                rescaler.scale16bitTo8bit(img, display);

                cv::imshow("image", display);
            }
            else {
                std::cout << "Image status was " << data.status << std::endl;
            }
        }

        cv::waitKey();
    }

}