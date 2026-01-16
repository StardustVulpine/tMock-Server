//
// Created by stardustvulpine on 15/1/26.
//

#include "FatalErrorMessage.hpp"
#include <MessageTypes.h>

namespace tmockserver::messages {
    FatalErrorMessage::FatalErrorMessage (
        const TextModes textMode,
        const std::string_view text
    ) : BaseMessage(text.size()+2, MessageTypes::FATAL_ERROR) {
        m_networkTextMode = static_cast<char>(textMode);
        m_textSize = text.size();
        m_textContent = text;
    }

    void FatalErrorMessage::Print() const {

    }

    std::pair<std::unique_ptr<char[]>, size_t> FatalErrorMessage::GetContent() {
        auto buffer = CreateBuffer();
        char* ptr = buffer.get();

        ptr += Size();
        *ptr++ = m_networkTextMode;
        *ptr++ = m_textSize;
        std::copy_n(m_textContent.data(), m_textSize, ptr);
        ptr = buffer.get();
        size_t s = *reinterpret_cast<short int*>(ptr);

        return std::make_pair(std::move(buffer), s);
    }
} // tmockserver