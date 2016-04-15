#include <zmq.hpp>
#include <types/CameraData.h>
#include <io/CameraDataDeserializer.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <comm/TCPCameraCommsSub.h>
#include <unistd.h>

int main() {

    zmq::context_t context;
    TCPCameraCommsSub sub(context, "localhost", "5555");
    zmq::socket_t pairSocket(context, ZMQ_PAIR);
    pairSocket.connect("inproc://CameraSubObstacleDetectionPair");

    zmq::message_t request;
    zmq::message_t reply;


    while (true) {
        pairSocket.send(request);
        pairSocket.recv(&reply);

        std::vector<CameraData> dataVector = CameraDataDeserializer::deserializeFromZmq(reply);

        std::cout << "Received data from " << dataVector.size() << " cameras!" << std::endl;

        for (CameraData data : dataVector) {
            if (data.status == OK) {
                Image16bit img = data.frame;
                cv::imshow("image", img);
            }
            else {
                std::cout << "Image status was " << data.status << std::endl;
            }
        }

        cv::waitKey(0);
    }

}