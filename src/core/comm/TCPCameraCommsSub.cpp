#include "TCPCameraCommsSub.h"
#include "types/CameraData.h"

//sub loop interrupt flag
int TCPCameraCommsSub::interrupt = false;


void TCPCameraCommsSub::startSubscriber(zmq::context_t context, const std::string &endpointAddress,
                                        const std::string &portNumber){

    //initialize sub socket and inproc obstacle detection socket
    zmq::socket_t imgSubSocket(context, ZMQ_SUB);
    zmq::socket_t ipcObDecSocket(context, ZMQ_REP);

    //sets message filter on sub socket to accept all messages
    imgSubSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //connects and binds sub and inproc sockets, respectively
    imgSubSocket.connect(("tcp://" + endpointAddress + ":" + portNumber).c_str());
    ipcObDecSocket.bind("inproc://CameraSubObstacleDetectionPair");

    //actual sub loop for recieving messages
    //TODO: implement something that actually watches for an interrupt, look at TCPImageServer.cpp
    while (!interrupt){
        try {
            // TODO: handle different statuses (Check CameraData.h)

            //create poll item which will check for sub and inproc sockets being triggered
            // ZMQ_POLLIN allows at least one message to be recieved from any socket without blocking
            zmq_pollitem_t items[2];
            items[0].socket = (void *) imgSubSocket;
            items[0].events = ZMQ_POLLIN;
            items[0].revents = 0;
            items[1].socket = (void *) ipcObDecSocket;
            items[1].events = ZMQ_POLLIN;
            items[1].revents = 0;

            //creates messages to be sent/recieved
            zmq::message_t imageMessage;
            zmq::message_t requestMessage;
            zmq::message_t replyMessage;
            std::size_t size;

            //flag for imageMessage recieved
            bool imageRecieved = false;

            //loop checks for both sub socket and inproc socket being 'triggered'
            while(1) {
                int nsockets = zmq::poll((zmq_pollitem_t *) &items, 2, -1);
                //ask alan about this first if statement with nsockets
                if(nsockets < 1) {
                    std::cout << "bad" << std::endl;
                    break;
                }
                if(items[0].revents & ZMQ_POLLIN) {
                    imageRecieved = true; //update flag
                    imgSubSocket.recv(&imageMessage);
                    std::string str((char *) imageMessage.data(), imageMessage.size());
                    std::cout << str << std::endl;
                }
                if(items[1].revents & ZMQ_POLLIN & imageRecieved) {
                    replyMessage.copy(&imageMessage);
                    ipcObDecSocket.recv(&requestMessage);
                    ipcObDecSocket.send(replyMessage);
                    imageRecieved = false; //update flag
                }
            }

            // Deserialize.
            // TODO: imageMessage should hold size of image
//          cv::Mat container(_imageHeight, _imageWidth, CV_16UC1, reply.data());
//          cv::Mat newImage(_imageHeight, _imageWidth, CV_16UC1);
//          container.copyTo(newImage);
            CameraData* data = (CameraData*) imageMessage.data();
            size = sizeof(data);

            //  Send reply back to client
            memcpy((void *) replyMessage.data(), imageMessage.data(), size);

            imgSubSocket.send(replyMessage);

        } catch (zmq::error_t &e) {
            // TODO: Log that the server has received an interrupt signal.
            std::cout << "zmq error encountered " << std::endl;
        }//trycatch

        if (interrupt) {
            // TODO: Log that the server is shutting down.
            std::cout << "server shutting down due to interrupt" << std::endl;
            break;
        }
    }//while

    if (imgSubSocket.connected()) {
        imgSubSocket.close();
    }

    context.close();
}