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

        void Print() const override;
        //[[nodiscard]] std::unique_ptr<std::byte[]> Serialize() const override;
        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const override;


    private:
        std::byte m_networkTextMode{};
        std::byte m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver