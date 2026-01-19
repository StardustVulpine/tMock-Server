//
// Created by stardustvulpine on 1/17/26.
//

#include "RequestPasswordMessage.hpp"

#include <iostream>
#include "Exception.hpp"

namespace tmockserver::messages {
    RequestPasswordMessage::RequestPasswordMessage() : BaseMessage(3, MessageTypes::REQUEST_PASSWORD){}

    void RequestPasswordMessage::Send(const Socket &socket) const {
        try {
            const auto buffer = CreateBuffer();
            socket.Write(buffer.get(), Size());
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

