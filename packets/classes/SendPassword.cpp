//
// Created by stardustvulpine on 1/19/26.
//

#include "SendPassword.hpp"
#include <iostream>

#include "../enums/PacketType.hpp"

namespace tmockserver::messages {
    SendPassword::SendPassword
    (
        const std::size_t msgSize,
        std::unique_ptr<std::byte[]> &buffer,
        const networking::Socket &client_socket
    )
    : BaseMessage(msgSize, PacketType::RECEIVE_PASSWORD)
    {
        buffer = std::make_unique<std::byte[]>(msgSize);
        client_socket.Read(buffer.get() + BaseMessage::Size(), msgSize - BaseMessage::Size());
        std::byte* ptr = buffer.get();
        *reinterpret_cast<short int *>(ptr) = static_cast<short int>(msgSize);
        ptr += 2;
        *ptr = static_cast<std::byte>(PacketType::CONNECT_REQUEST);
        ptr++;
        m_passwordSize = static_cast<char>(*ptr);
        ptr++;
        const std::string_view txtContent (reinterpret_cast<char *>(ptr), m_passwordSize);
        m_passwordContent = txtContent;
    }

    void SendPassword::Print() const {
        BaseMessage::Print();

        std::println(std::cout, "Text Size: {:d}", m_passwordSize);
        std::println(std::cout, "Text Content: {}", m_passwordContent);
    }
}