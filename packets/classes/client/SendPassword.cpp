//
// Created by stardustvulpine on 1/19/26.
//

#include "SendPassword.hpp"
#include <iostream>

#include "../../enums/PacketType.hpp"

namespace tmockserver::packets {
    SendPassword::SendPassword
    (
        const std::size_t msgSize,
        std::unique_ptr<std::byte[]> &buffer,
        const networking::Socket &client_socket
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
    }

    void SendPassword::Print() const {
        std::println(std::cout, "\033[38;2;0;255;0m Client sent password. \033[0m");
        BasePacket::Print();

        std::println(std::cout, "Text Size: {:d}", static_cast<char>(m_passwordSize));
        std::println(std::cout, R"(Text Content: "{}")", m_passwordContent);
    }
}