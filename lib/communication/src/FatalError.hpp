//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

#include "BasePacket.hpp"
#include "../include/NetworkTextMode.hpp"

namespace tmockserver::packets {
    class FatalError : public BasePacket {
    public:
        FatalError(NetworkTextMode textMode, std::string_view text);
        ~FatalError() override = default;

        void Print() const;
        void Send(const net::Socket &socket) const override;
        [[nodiscard]] std::pair<std::unique_ptr<std::byte[]>, size_t> GetContent() const;


    private:
        std::byte m_networkTextMode{};
        std::byte m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver