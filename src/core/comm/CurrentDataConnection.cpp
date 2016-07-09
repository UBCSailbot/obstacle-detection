#include "CurrentDataConnection.h"

CurrentDataConnection::CurrentDataConnection(zmq::context_t &context, std::string currentDataReceiveAddress) :
        currentDataSubscriber_(context, ZMQ_SUB) {
    // Initialize SUB socket for receiving current data from pi-controller
    // set message filter on sub socket to accept all messages
    currentDataSubscriber_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    currentDataSubscriber_.connect(currentDataReceiveAddress.c_str());
}

bool CurrentDataConnection::checkForCurrentData() {
    if (currentDataSubscriber_.recv(&newCurrentData_, ZMQ_NOBLOCK)) {
        // copy the message containing the latest current data so that it
        // doesn't get overwritten by subsequent calls to this function.
        CurrentDataDeserializer currentDataDeserializer;
        currentData_ =
                currentDataDeserializer.deserialize(
                        std::string(static_cast<char *> (newCurrentData_.data()), newCurrentData_.size()));
        return true;
    }
    return false;
}


CurrentData CurrentDataConnection::getBoatData() {
    checkForCurrentData();
    return currentData_;
}
