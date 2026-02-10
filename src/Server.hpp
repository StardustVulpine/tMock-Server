//
// Created by stardustvulpine on 2/10/26.
//

#pragma once

#include <Socket.hpp>

constexpr int SERVER_PROTOCOL_VERSION = 317;
constexpr int DEFAULT_PORT = 7777;
constexpr int DEFAULT_MAX_CLIENTS = 8;

using namespace tmockserver::networking;

namespace tmockserver
{
    class Server
    {
        struct Config
        {
            int port = DEFAULT_PORT;
            int max_clients = DEFAULT_MAX_CLIENTS;
            std::optional<std::string> password = std::nullopt;
        };


        public:
        explicit Server();
        void Start();

        private:
        int m_serverVersion = SERVER_PROTOCOL_VERSION;
        Socket m_socket;
        Config m_config = Config();

        [[noreturn]] void Run();
    };
} // tmockserver