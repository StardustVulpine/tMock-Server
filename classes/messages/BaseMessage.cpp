//
// Created by stardustvulpine on 1/11/26.
//

#include "BaseMessage.hpp"
#include <iostream>

namespace tmockserver::messages {
    BaseMessage::BaseMessage(std::stringstream &stream) {
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        stream.read(&type, sizeof(type));
    }

    void BaseMessage::Print() const {
        std::println(std::cout, "Message Size: {}", size);
        std::println(std::cout, "Message Type: {:d}", type);
    }

} // tmockserver::messages