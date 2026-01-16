//
// Created by stardustvulpine on 1/11/26.
//

#include "ConnectRequest.hpp"
#include <iostream>

namespace tmockserver::messages {
    ConnectRequest::ConnectRequest(std::stringstream stream) : BaseMessage(stream) {
        stream.read(&m_textSize, sizeof(m_textSize));
        stream.read(m_textContent.data(), MAX_TEXT_LENGTH);
        m_textContent[MAX_TEXT_LENGTH] = '\0';
    }

    ConnectRequest::ConnectRequest
    (
        const std::size_t msgSize,
        const std::size_t txtSize,
        const char *text
    ) : BaseMessage(msgSize, MessageTypes::CONNECT_REQUEST), m_textSize(txtSize)
    {
        std::copy_n(text, txtSize, m_textContent.data());
        m_textContent[MAX_TEXT_LENGTH] = '\0';
    }

    void ConnectRequest::Print() const {
        BaseMessage::Print();
        std::println(std::cout, "Text Size: {:d}", m_textSize);
        std::println(std::cout, "Text Content: {}", m_textContent);
        std::println(std::cout, "---");
    }
} // tmockserver::messages