//
// Created by stardustvulpine on 1/10/26.
//

#pragma once

#include <optional>
#include <string>
#include <netinet/in.h>

#include "../enums/AddressFamily.h"
#include "../enums/ConnectionType.h"

using Socket_T = int;

constexpr Socket_T INVALID_SOCKET = -1;

namespace tmockserver {
    class Socket {
        public:
        Socket() = default;
        Socket(AddressFamily address_family, ConnectionType connection_type); // Server socket constructor
        Socket(Socket_T socket); // Client socket constructor
        ~Socket();

        bool Bind(unsigned short int port, const std::optional<std::string> &ip_address=std::nullopt);
        void Listen() const;
        [[nodiscard]] Socket Accept() const;
        void Read(void *buffer, unsigned int size) const;
        void Write(const void *buffer, unsigned int size) const;

        private:
        Socket_T m_socket = INVALID_SOCKET; // Variable for storing socket created in constructor
        sockaddr_in m_address{}; //
        int m_address_family{}; // Variable for storing IP address family (IPv4 or IPv6)

    };
} // tmockserver

