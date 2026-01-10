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

namespace tmockserver {
    class Socket {
        public:
        Socket(AdressFamily adress_family, ConnectionType connection_type);
        bool Bind(unsigned short int port, std::optional<std::string> ip_adress=std::nullopt);

        operator int() const { return m_socket; }


        private:
        Socket_T m_socket;
        sockaddr_in m_address{};
        int m_adress_family;

    };
} // tmockserver

