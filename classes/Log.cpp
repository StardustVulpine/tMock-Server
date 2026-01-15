//
// Created by stardustvulpine on 1/11/26.
//

#include "Log.hpp"

namespace tmockserver::messagelogger {

    void Log::InitMessage(init_message msg, std::string payload) {
        printf("Message Size: %i \n", msg.size);
        printf("Message Type: %i \n", msg.type);
        printf("Message: %s \n", payload.c_str());
    }

} // tmockserver