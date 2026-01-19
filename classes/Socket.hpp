//
// Created by stardustvulpine on 1/10/26.
//

#pragma once

#include <optional>
#include <string>
#include <netinet/in.h>
#include <format>

#include "../enums/AddressFamily.h"
#include "../enums/ConnectionType.h"

using Socket_T = int;

constexpr Socket_T INVALID_SOCKET = -1;

namespace tmockserver {
    class Socket {
    public:
        Socket() = default;
        Socket(AddressFamily address_family, ConnectionType connection_type); // Server socket constructor
        Socket(Socket_T socket, sockaddr_in address); // Client socket constructor
        ~Socket();

        Socket(const Socket& socket) = delete;
        Socket& operator=(const Socket& socket) = delete;

        Socket(Socket&& socket);
        Socket& operator=(Socket&& socket);

        bool Bind(unsigned short int port, const std::optional<std::string> &ip_address=std::nullopt);
        void Listen() const;
        [[nodiscard]] Socket Accept() const;
        void Read(void *buffer, unsigned int size) const;
        void Write(const void *buffer, unsigned int size) const;

        [[nodiscard]] std::string GetAddress() const;

    private:
        Socket_T m_socket = INVALID_SOCKET; // Variable for storing socket created in constructor
        sockaddr_in m_address{}; //
        int m_address_family{}; // Variable for storing IP address family (IPv4 or IPv6)

    };


} // tmockserver

template <>
struct std::formatter<tmockserver::Socket> : std::formatter<std::string> {
    auto format(const tmockserver::Socket &socket, format_context& ctx) const {
        return formatter<string>::format(
          std::format("[Socket Details]\n IP Address: {}", socket.GetAddress()), ctx);
    }
};


