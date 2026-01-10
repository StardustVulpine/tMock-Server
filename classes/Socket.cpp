//
// Created by stardustvulpine on 1/10/26.
//

#include "Socket.h"

#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace tmockserver {
    Socket::Socket(AdressFamily adress_family, ConnectionType connection_type) {

        m_adress_family = adress_family == AdressFamily::IPv4 ? AF_INET : AF_INET6;
        int connType = connection_type == ConnectionType::TCP ? SOCK_STREAM : SOCK_DGRAM;

        m_socket = socket(m_adress_family, connType, 0);
    }

    bool Socket::Bind(unsigned short int port, std::optional<std::string> ip_adress) {
        m_address.sin_port = htons(port);
        m_address.sin_family = m_adress_family;
        if (ip_adress.has_value()) {
            inet_pton(m_adress_family, ip_adress.value().c_str(), &m_address.sin_addr);
        } else {
            m_address.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        bind(m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address));
    }
} // tmockserver