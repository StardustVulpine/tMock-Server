//
// Created by stardustvulpine on 1/19/26.
//

#include "../include/SendPassword.hpp"
#include <iostream>

namespace tmockserver::packets {
    SendPassword::SendPassword(const std::size_t packetSize, std::unique_ptr<std::byte[]> &buffer, const net::Socket &client_socket)
    : Packet(packetSize, PacketType::RECEIVE_PASSWORD)
    {
        buffer = std::make_unique<std::byte[]>(PacketSize());
        client_socket.Read(buffer.get() + PacketHeadSize(), PacketSize() - PacketHeadSize());
        std::byte* ptr = buffer.get();
        *reinterpret_cast<short int *>(ptr) = static_cast<short int>(packetSize);
        ptr += 2;
        *ptr = static_cast<std::byte>(PacketType::CONNECT_REQUEST);
        ptr++;
        m_passwordSize = *ptr;
        ptr++;
        const std::string_view txtContent (reinterpret_cast<char *>(ptr), std::to_integer<size_t>(m_passwordSize));
        m_passwordContent = txtContent;

        SendPassword::Print();
    }

    void SendPassword::Print() const {
        PrintPacketHead(Direction::RECEIVE);
        std::println(std::cout, R"(  [PAYLOAD] TextSize: {:d}; TextContent: "{}")", static_cast<char>(m_passwordSize), m_passwordContent);
    }
}