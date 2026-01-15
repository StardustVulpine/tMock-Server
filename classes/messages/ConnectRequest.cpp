//
// Created by stardustvulpine on 1/11/26.
//

#include "ConnectRequest.hpp"
#include <iostream>

namespace tmockserver::messages {
    ConnectRequest::ConnectRequest(std::stringstream stream) : BaseMessage(stream) {
        stream.read(&textSize, sizeof(textSize));
        stream.read(textContent, MAX_TEXT_LENGTH);
        textContent[MAX_TEXT_LENGTH] = '\0';
    }

    void ConnectRequest::Print() const {
        BaseMessage::Print();
        std::println(std::cout, "Text Size: {:d}", textSize);
        std::println(std::cout, "Text Content: {}", textContent);
        std::println(std::cout, "---");
    }
} // tmockserver::messages