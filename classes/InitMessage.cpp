//
// Created by stardustvulpine on 1/11/26.
//

#include "InitMessage.hpp"
#include <iostream>

namespace tmockserver::messages {
    InitMessage::InitMessage(std::stringstream stream) : BaseMessage(stream) {
        stream.read(&textSize, sizeof(textSize));
        stream.read(textContent, MAX_TEXT_LENGTH);
        textContent[MAX_TEXT_LENGTH] = '\0';
    }

    void InitMessage::Print() const {
        BaseMessage::Print();
        std::println(std::cout, "Text Size: {:d}", textSize);
        std::println(std::cout, "Text Content: {}", textContent);
    }
} // tmockserver::messages