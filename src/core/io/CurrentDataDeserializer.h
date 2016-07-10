//
// Created by josh on 20/06/16.
//

#ifndef ROUTEMAKING_CURRENTDATADESERIALIZER_H
#define ROUTEMAKING_CURRENTDATADESERIALIZER_H

#include <sstream>
#include <types/CurrentData.h>
#include <string>

class CurrentDataDeserializer {
public:
    static CurrentData deserialize(const std::string inputCurrentData);
};


#endif //ROUTEMAKING_CURRENTDATADESERIALIZER_H
