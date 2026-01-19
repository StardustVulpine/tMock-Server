//
// Created by stardustvulpine on 1/11/26.
//

#include "ConnectRequest.hpp"
#include <iostream>
#include <utility>

namespace tmockserver::messages {
    ConnectRequest::ConnectRequest(std::stringstream stream) : BaseMessage(stream)
    {
        stream.read(&m_textSize, sizeof(m_textSize));
        stream.read(m_textContent.data(), MAX_TEXT_LENGTH);
        m_textContent[MAX_TEXT_LENGTH] = '\0';
    }

    ConnectRequest::ConnectRequest(const std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const Socket& client_socket)
    : BaseMessage(msgSize, MessageTypes::CONNECT_REQUEST)
    {
        buffer = std::make_unique<std::byte[]>(msgSize);
        client_socket.Read(buffer.get() + BaseMessage::Size(), msgSize - BaseMessage::Size());
        std::byte* ptr = buffer.get();
        *reinterpret_cast<short int *>(ptr) = static_cast<short int>(msgSize);
        ptr += 2;
        *ptr = static_cast<std::byte>(MessageTypes::CONNECT_REQUEST);
        ptr++;
        m_textSize = static_cast<char>(*ptr);
        ptr++;
        const std::string_view txtContent (reinterpret_cast<char *>(ptr), m_textSize);
        m_textContent = txtContent;
    }

    ConnectRequest::ConnectRequest
    (
        const std::size_t msgSize,
        const std::size_t txtSize,
        std::string text
    ) : BaseMessage(msgSize, MessageTypes::CONNECT_REQUEST), m_textSize(static_cast<char>(txtSize)), m_textContent(std::move(text))
    {
    }

    ConnectRequest ConnectRequest::Get(const Socket &socket) {
        const auto msgBuffer = std::make_unique<char[]>(Size());
        socket.Read(msgBuffer.get(), Size());
        std::stringstream ss;
        ss.write(msgBuffer.get(), Size());
        ConnectRequest i_msg(std::move(ss));

        return i_msg;
    }

    void ConnectRequest::Print() const {
        BaseMessage::Print();

        std::println(std::cout, "Text Size: {:d}", m_textSize);
        std::println(std::cout, "Text Content: {}", m_textContent);
        std::println(std::cout, "---");
    }
} // tmockserver::messages