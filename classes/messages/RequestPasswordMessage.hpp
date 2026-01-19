//
// Created by stardustvulpine on 1/17/26.
//

#pragma once
#include "BaseMessage.hpp"

namespace tmockserver::messages {
    class RequestPasswordMessage : public BaseMessage {
    public:
        RequestPasswordMessage();
        void Send(const Socket &socket) const override;
    };
}
