//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

#include "Packet.hpp"
#include <Log.hpp>

using Console = stardustvulpine::Console::Logger::Log;

namespace tmockserver::packets {
    class FatalError : public Packet {
    public:
        FatalError(NetworkTextMode textMode, const std::string_view text) : Packet(text.size()+5, PacketType::FATAL_ERROR),
        m_networkTextMode(static_cast<std::byte>(textMode)), m_textSize(static_cast<std::byte>(text.size())), m_textContent(text)
        {

        }
        ~FatalError() override = default;

        void Print() const override
        {
            PrintPacketHead(Direction::OUTGOING);
            std::println(std::cout, "  [PAYLOAD] NetworkTextMode: LITERAL, TextSize: {}, TextContent: {}", static_cast<int>(m_textSize), m_textContent);
        }

        [[nodiscard]] std::string GetPacketPayloadAsString() const
        {
            return std::format("{}\n[PAYLOAD] NetworkTextMode: LITERAL, TextSize: {}, TextContent: {}", GetPacketHeadAsString(Direction::OUTGOING), static_cast<int>(m_textSize), m_textContent);
        }

        /*template <typename T> T Get() {
            if (std::is_same_v<T, std::string>) {
                 return std::format("{}\n[PAYLOAD] NetworkTextMode: LITERAL, TextSize: {}, TextContent: {}", GetPacketHeadAsString(Direction::OUTGOING), static_cast<int>(m_textSize), m_textContent);
            }
            if (std::is_same_v<T, FatalError>) {
                return *this;
            }
            // Add error catching when typename doesn't match at all (ex. if int is provided)
            return 0;
        }*/

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