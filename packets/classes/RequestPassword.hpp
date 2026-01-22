//
// Created by stardustvulpine on 1/17/26.
//

#pragma once
#include "BaseMessage.hpp"

namespace tmockserver::messages {
    class RequestPassword : public BaseMessage {
    public:
        RequestPassword();
        void Send(const networking::Socket &socket) const override;
    };
}
