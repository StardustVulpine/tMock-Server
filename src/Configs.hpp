//
// Created by stardustvulpine on 2/1/26.
//

#pragma once
#include <string>

namespace tmockserver {
    struct ServerConfig {
        int port;
        int max_connections;
        std::string password;
    };
}
