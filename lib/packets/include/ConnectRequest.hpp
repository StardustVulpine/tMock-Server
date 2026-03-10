//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <expected>
#include "Packet.hpp"

namespace tmockserver::packets {
    class ConnectRequest : public Packet {
    public:
        enum class VersionError { BadVersion = 0 };

        ConnectRequest(const std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const net::Socket& client_socket)
        : Packet(msgSize, PacketType::CONNECT_REQUEST)
        {
            buffer = std::make_unique<std::byte[]>(msgSize);
            client_socket.Read(buffer.get() + Packet::PacketHeadSize(), msgSize - Packet::PacketHeadSize());
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

        ~ConnectRequest() override = default;

        void Print() const override {
            PrintPacketHead(Direction::INCOMING);
            std::println(std::cout, R"(  [PAYLOAD] TextSize: {:d}; TextContent: "{}")", static_cast<char>(m_textSize), m_textContent);
        }


        [[nodiscard]] std::expected<int, VersionError> GetClientVersion() const {
            const std::string ver_s = m_textContent.substr(8,3);
            if (int version{}; std::from_chars(ver_s.data(), ver_s.data() + ver_s.length(), version)) {
                return version;
            }
            return std::unexpected(VersionError::BadVersion);
        }

    private:
        std::byte m_textSize{};
        std::string m_textContent{};

        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(const std::unique_ptr<std::byte[]> buffer) const override
        {
            const std::byte* ptr = buffer.get();
            (void) ptr; // :C
            return nullptr;
        }

    };
} // tmockserver::messages