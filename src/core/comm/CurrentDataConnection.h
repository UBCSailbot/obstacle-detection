#ifndef ROUTEMAKING_CURRENTDATACONNECTION_H
#define ROUTEMAKING_CURRENTDATACONNECTION_H

#include <zmq.hpp>
#include <types/CurrentData.h>
#include <io/CurrentDataDeserializer.h>
#include <io/BoatDataStream.h>

class CurrentDataConnection : public BoatDataStream {

public:
    virtual CurrentData getBoatData() override;

    CurrentDataConnection(zmq::context_t &context, std::string currentDataReceiveAddress);

    bool checkForCurrentData();

private:
    zmq::socket_t currentDataSubscriber_;
    zmq::message_t newCurrentData_;
    CurrentData currentData_;
};


#endif //ROUTEMAKING_CURRENTDATACONNECTION_H
