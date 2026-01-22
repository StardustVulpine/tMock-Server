//
// Created by stardustvulpine on 15/1/26.
//

#include "FatalError.hpp"

#include <iostream>

#include <Exception.hpp>

namespace tmockserver::messages {
    FatalError::FatalError (
        const NetworkTextMode textMode,
        const std::string_view text
    ) : BaseMessage(text.size()+5, PacketType::FATAL_ERROR) {
        m_networkTextMode = static_cast<char>(textMode);
        m_textSize = text.size();
        m_textContent = text;
    }

    void FatalError::Print() const {

    }

    void FatalError::Send(const networking::Socket &socket) const {
        try {
            auto [fst, snd] = GetContent();
            socket.Write(fst.get(), snd);
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::pair<std::unique_ptr<char[]>, size_t> FatalError::GetContent() const {
        auto buffer = CreateBuffer();
        char* ptr = buffer.get();

        ptr += Size();
        *ptr++ = static_cast<char>(m_networkTextMode);
        *ptr++ = static_cast<char>(m_textSize);
        std::copy_n(m_textContent.data(), m_textSize, ptr);
        ptr = buffer.get();
        size_t s = *reinterpret_cast<short int*>(ptr);

        return std::make_pair(std::move(buffer), s);
    }


} // tmockserver