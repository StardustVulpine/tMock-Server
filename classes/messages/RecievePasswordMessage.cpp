//
// Created by stardustvulpine on 1/19/26.
//

#include "RecievePasswordMessage.hpp"

#include <iostream>

namespace tmockserver::messages {
    RecievePasswordMessage::RecievePasswordMessage
    (
        const std::size_t msgSize,
        std::unique_ptr<std::byte[]> &buffer,
        const Socket &client_socket
    )
    : BaseMessage(msgSize, MessageTypes::RECEIVE_PASSWORD)
    {
        buffer = std::make_unique<std::byte[]>(msgSize);
        client_socket.Read(buffer.get() + BaseMessage::Size(), msgSize - BaseMessage::Size());
        std::byte* ptr = buffer.get();
        *reinterpret_cast<short int *>(ptr) = static_cast<short int>(msgSize);
        ptr += 2;
        *ptr = static_cast<std::byte>(MessageTypes::CONNECT_REQUEST);
        ptr++;
        m_passwordSize = static_cast<char>(*ptr);
        ptr++;
        const std::string_view txtContent (reinterpret_cast<char *>(ptr), m_passwordSize);
        m_passwordContent = txtContent;
    }

    void RecievePasswordMessage::Print() const {
        BaseMessage::Print();

        std::println(std::cout, "Text Size: {:d}", m_passwordSize);
        std::println(std::cout, "Text Content: {}", m_passwordContent);
    }
}