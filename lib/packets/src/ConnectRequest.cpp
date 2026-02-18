//
// Created by stardustvulpine on 1/11/26.
//

#include "ConnectRequest.hpp"

#include <iostream>

namespace tmockserver::packets {
    ConnectRequest::ConnectRequest(const std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const net::Socket& client_socket)
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

        ConnectRequest::Print();
    }

    void ConnectRequest::Print() const {
        PrintPacketHead(PacketDirection::RECEIVE);
        std::println(std::cout, R"(  [PAYLOAD] TextSize: {:d}; TextContent: "{}")", static_cast<char>(m_textSize), m_textContent);
    }

    std::expected<int, ConnectRequest::VersionError> ConnectRequest::GetClientVersion() const {
        int version{};
        std::string ver_s = m_textContent.substr(8,3);
        if (std::from_chars(ver_s.data(), ver_s.data() + ver_s.length(), version)) {
            return version;
        }
        return std::unexpected(VersionError::BadVersion);
    }
} // tmockserver::messages
