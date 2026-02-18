//
// Created by stardustvulpine on 1/19/26.
//

#include "SendPassword.hpp"
#include <iostream>

#include <PacketType.hpp>

namespace tmockserver::packets {
    SendPassword::SendPassword
    (
        const std::size_t msgSize,
        std::unique_ptr<std::byte[]> &buffer,
        const net::Socket &client_socket
    )
    : BasePacket(msgSize, PacketType::RECEIVE_PASSWORD)
    {
        buffer = std::make_unique<std::byte[]>(msgSize);
        client_socket.Read(buffer.get() + BasePacket::Size(), msgSize - BasePacket::Size());
        std::byte* ptr = buffer.get();
        *reinterpret_cast<short int *>(ptr) = static_cast<short int>(msgSize);
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
        PrintPacketHead(PacketDirection::RECEIVE);
        std::println(std::cout, R"(  [PAYLOAD] TextSize: {:d}; TextContent: "{}")", static_cast<char>(m_passwordSize), m_passwordContent);
    }
}