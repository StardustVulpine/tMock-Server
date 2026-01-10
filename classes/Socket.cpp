//
// Created by stardustvulpine on 1/10/26.
//

#include "Socket.h"
#include "Exception.h"

#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

namespace tmockserver {
    Socket::Socket(AdressFamily adress_family, ConnectionType connection_type) {

        m_adress_family = adress_family == AdressFamily::IPv4 ? AF_INET : AF_INET6;
        int connType = connection_type == ConnectionType::TCP ? SOCK_STREAM : SOCK_DGRAM;

        m_socket = socket(m_adress_family, connType, 0);
    }

    Socket::Socket(Socket_T socket) : m_socket(socket) {
        if (m_socket == INVALID_SOCKET) throw Exception(strerror(errno));
    }

    bool Socket::Bind(unsigned short int port, std::optional<std::string> ip_adress) {
        m_address.sin_port = htons(port);
        m_address.sin_family = m_adress_family;
        if (ip_adress.has_value()) {
            inet_pton(m_adress_family, ip_adress.value().c_str(), &m_address.sin_addr);
        } else {
            m_address.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        return bind(m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) == 0;
    }

    void Socket::Listen() {
        if (listen(m_socket, SOMAXCONN) == -1) throw Exception(strerror(errno));
    }

    Socket Socket::Accept() {
        sockaddr_in client_addr {};
        int client_len = sizeof(client_addr);
        return Socket(accept(m_socket, reinterpret_cast<sockaddr*>(&client_addr), reinterpret_cast<socklen_t*>(&client_len)));
    }

    void Socket::Read(void *buffer, unsigned int size) {
        read(m_socket, buffer, size);
    }
} // tmockserver