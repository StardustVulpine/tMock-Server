//
// Created by stardustvulpine on 1/10/26.
//

#include "Socket.hpp"
#include "Exception.hpp"

#include <memory>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

namespace tmockserver {
    /* Constructor for server socket
     * Takes:
     * address_family - from enum (AddressFamily::IPv4 or AddressFamily::IPv6)
     * connection_type - from enum (ConnectionType::TCP or ConnectionType::UDP)
     *
     * Construct's server socket and saves it to object's private parameter
     */
    Socket::Socket(AddressFamily address_family, ConnectionType connection_type) {

        // Sets address family and connection type for Server Socket object based on provided enum types using built into system C Library for handling sockets
        m_address_family = address_family == AddressFamily::IPv4 ? AF_INET : AF_INET6;
        const int connType = connection_type == ConnectionType::TCP ? SOCK_STREAM : SOCK_DGRAM;

        // Creates socket and saves it as object's private parameter
        m_socket = socket(m_address_family, connType, 0);
    }

    /* Constructor for client socket
     *
     */
    Socket::Socket(Socket_T socket) : m_socket(socket) {
        if (m_socket == INVALID_SOCKET) throw Exception(strerror(errno));
    }

    /* Deconstructor for socket objects */
    Socket::~Socket() {
        //close(m_socket);
    }

    /* Method for binding server's socket to specified port with optional filter for specific IP address
     * Takes:
     * port: int - value of the port (ex. value: 7777)
     * (optional) ip_address: string - IP Address on which socket should be bound (ex. value: "192.168.1.10")
     *
     * Returns ...
     */
    bool Socket::Bind(const unsigned short int port, const std::optional<std::string> &ip_address) {

        // Set port and address family to object's parameters
        m_address.sin_port = htons(port); // Saved in network byte order
        m_address.sin_family = m_address_family; // m_address_family parameter is assigned during object's construction

        // Checks if IP Address is provided, if so
        if (ip_address.has_value()) {
            inet_pton(m_address_family, ip_address.value().c_str(), &m_address.sin_addr);
        } else {
            m_address.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        return bind(m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) == 0;
    }

    void Socket::Listen() const {
        if (listen(m_socket, SOMAXCONN) == -1) throw Exception(strerror(errno));
    }

    Socket Socket::Accept() const {
        sockaddr_in client_addr {};
        int client_len = sizeof(client_addr);
        return {accept(m_socket, reinterpret_cast<sockaddr*>(&client_addr), reinterpret_cast<socklen_t*>(&client_len))};
    }

    void Socket::Read(void *buffer, unsigned int size) const {
        read(m_socket, buffer, size);
    }
} // tmockserver