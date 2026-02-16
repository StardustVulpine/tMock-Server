//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <expected>
#include "BasePacket.hpp"
#include "../include/PacketType.hpp"

namespace tmockserver::packets {
    class ConnectRequest : public BasePacket {
    public:
        enum class VersionError {
            BadVersion = 0
        };

        ConnectRequest(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const net::Socket& client_socket);

        ~ConnectRequest() override = default;

        void Print() const override;

        [[nodiscard]] std::expected<int, VersionError> GetClientVersion() const;

    private:
        std::byte m_textSize{};
        std::string m_textContent{};

        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(const std::unique_ptr<std::byte[]> buffer) const override
        {
            std::byte* ptr = buffer.get();
            (void) ptr; // :C
            return nullptr;
        }

    };
} // tmockserver::messages