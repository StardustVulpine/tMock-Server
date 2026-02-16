//
// Created by stardustvulpine on 15/1/26.
//

#include "FatalError.hpp"
#include <iostream>
#include <Exception.hpp>

namespace tmockserver::packets {
    FatalError::FatalError (
        const NetworkTextMode textMode,
        const std::string_view text
    ) : BasePacket(text.size()+5, PacketType::FATAL_ERROR) {
        m_networkTextMode = static_cast<std::byte>(textMode);
        m_textSize = static_cast<std::byte>(text.size());
        m_textContent = text;
    }

    void FatalError::Print() const {
        PrintPacketHead(1);
        std::println(std::cout, "  [PAYLOAD] NetworkTextMode: LITERAL, TextSize: {}, TextContent: {}", static_cast<int>(m_textSize), m_textContent);
    }

    std::unique_ptr<std::byte[]> FatalError::GetPacketContent(std::unique_ptr<std::byte[]> buffer) const
    {
        std::byte* ptr = buffer.get();
        ptr += Size();

        *ptr++ = m_networkTextMode;
        *ptr++ = m_textSize;
        std::copy_n(reinterpret_cast<const std::byte *>(m_textContent.data()), std::to_integer<size_t>(m_textSize), ptr);

        return buffer;
    }
} // tmockserver