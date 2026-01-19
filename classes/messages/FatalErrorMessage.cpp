//
// Created by stardustvulpine on 15/1/26.
//

#include "FatalErrorMessage.hpp"

#include <iostream>
#include <MessageTypes.h>

#include "Exception.hpp"

namespace tmockserver::messages {
    FatalErrorMessage::FatalErrorMessage (
        const TextModes textMode,
        const std::string_view text
    ) : BaseMessage(text.size()+5, MessageTypes::FATAL_ERROR) {
        m_networkTextMode = static_cast<char>(textMode);
        m_textSize = text.size();
        m_textContent = text;
    }

    void FatalErrorMessage::Print() const {

    }

    void FatalErrorMessage::Send(const Socket &socket) const {
        try {
            auto [fst, snd] = GetContent();
            socket.Write(fst.get(), snd);
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::pair<std::unique_ptr<char[]>, size_t> FatalErrorMessage::GetContent() const {
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