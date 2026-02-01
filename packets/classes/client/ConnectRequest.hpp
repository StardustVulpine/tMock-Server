//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <expected>

#include "../BasePacket.hpp"
#include "../../enums/PacketType.hpp"

namespace tmockserver::packets {
    class ConnectRequest : public BasePacket {
    public:
        enum class VersionError {
            BadVersion = 0
        };

        ConnectRequest(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const networking::Socket& client_socket);
        ConnectRequest(std::size_t msgSize, std::size_t txtSize, std::string  text);

        ~ConnectRequest() override = default;

        void Print() const override;

        std::expected<int, VersionError> GetClientVersion() const;



    private:
        std::byte m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver::messages