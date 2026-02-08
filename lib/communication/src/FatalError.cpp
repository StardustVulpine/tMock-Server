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

    }

    void FatalError::Send(const networking::Socket &socket) const {
        try {
            auto [buffer, size] = GetContent();
            socket.Write(buffer.get(), size);
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::pair<std::unique_ptr<std::byte[]>, size_t> FatalError::GetContent() const {
        auto buffer = CreateBuffer();
        std::byte* ptr = buffer.get();
        ptr += Size();

        *ptr++ = m_networkTextMode;
        *ptr++ = m_textSize;
        std::copy_n(reinterpret_cast<const std::byte *>(m_textContent.data()), std::to_integer<size_t>(m_textSize), ptr);
        ptr = buffer.get();
        size_t s = *reinterpret_cast<short int*>(ptr);

        return std::make_pair(std::move(buffer), s);
    }


} // tmockserver