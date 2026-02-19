//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

#include "Packet.hpp"

namespace tmockserver::packets {
    class FatalError : public Packet {
    public:
        FatalError(NetworkTextMode textMode, const std::string_view text)  : Packet(text.size()+5, PacketType::FATAL_ERROR),
            m_networkTextMode(static_cast<std::byte>(textMode)), m_textSize(static_cast<std::byte>(text.size())), m_textContent(text) {}
        ~FatalError() override = default;

        void Print() const override
        {
            PrintPacketHead(Direction::SEND);
            std::println(std::cout, "  [PAYLOAD] NetworkTextMode: LITERAL, TextSize: {}, TextContent: {}", static_cast<int>(m_textSize), m_textContent);
        }

        //[[nodiscard]] std::unique_ptr<std::byte[]> Serialize() const override;
        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const override
        {
            std::byte* ptr = buffer.get();
            ptr += PacketHeadSize();

            *ptr++ = m_networkTextMode;
            *ptr++ = m_textSize;
            std::copy_n(reinterpret_cast<const std::byte *>(m_textContent.data()), std::to_integer<size_t>(m_textSize), ptr);

            return buffer;
        }


    private:
        std::byte m_networkTextMode{};
        std::byte m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver