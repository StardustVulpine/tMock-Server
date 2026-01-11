//
// Created by stardustvulpine on 1/10/26.
//

#pragma once

#include <optional>
#include <string>
#include <netinet/in.h>

#include "../enums/AdressFamily.h"
#include "../enums/ConnectionType.h"

using Socket_T = int;

constexpr Socket_T INVALID_SOCKET = -1;

namespace tmockserver {
    class Socket {
        public:
        Socket() = default;
        Socket(AdressFamily adress_family, ConnectionType connection_type); // Server socket constructor
        Socket(Socket_T socket); // Client socket constructor
        ~Socket();

        bool Bind(unsigned short int port, std::optional<std::string> ip_adress=std::nullopt);
        void Listen();
        Socket Accept();
        void Read(void *buffer, unsigned int size);

        operator int() const { return m_socket; }


        private:
        Socket_T m_socket = INVALID_SOCKET;
        sockaddr_in m_address{};
        int m_adress_family{};

    };
} // tmockserver

