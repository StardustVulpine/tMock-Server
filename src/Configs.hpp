//
// Created by stardustvulpine on 2/1/26.
//

#pragma once
#include <string>

namespace tmockserver {
    struct ServerConfig {
        int server_version{};
        int port{};
        int max_clients{};
        std::string password;

        ServerConfig() = default;

        ServerConfig(int server_version, int port, int max_clients, const std::string &password);
    };
}
