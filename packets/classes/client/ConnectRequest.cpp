//
// Created by stardustvulpine on 1/11/26.
//

#include "ConnectRequest.hpp"

#include <iostream>
#include <utility>

namespace tmockserver::packets {
    ConnectRequest::ConnectRequest(const std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const networking::Socket& client_socket)
    : BasePacket(msgSize, PacketType::CONNECT_REQUEST)
    {
        buffer = std::make_unique<std::byte[]>(msgSize);
        client_socket.Read(buffer.get() + BasePacket::Size(), msgSize - BasePacket::Size());
        std::byte* ptr = buffer.get();
        *reinterpret_cast<short int *>(ptr) = static_cast<short int>(msgSize);
        ptr += 2;
        *ptr = static_cast<std::byte>(PacketType::CONNECT_REQUEST);
        ptr++;
        m_textSize = *ptr;
        ptr++;
        const std::string_view txtContent (reinterpret_cast<char *>(ptr), std::to_integer<size_t>(m_textSize));
        m_textContent = txtContent;
    }

    ConnectRequest::ConnectRequest
    (
        const std::size_t msgSize,
        const std::size_t txtSize,
        std::string text
    ) : BasePacket(msgSize, PacketType::CONNECT_REQUEST), m_textSize(static_cast<std::byte>(txtSize)), m_textContent(std::move(text))
    {
    }

    void ConnectRequest::Print() const {
        std::println(std::cout, "\033[38;2;0;255;0m Client requested connection. \033[0m");
        BasePacket::Print();

        std::println(std::cout, "Text Size: {:d}", static_cast<char>(m_textSize));
        std::println(std::cout, R"(Text Content: "{}")", m_textContent);
    }
} // tmockserver::messages