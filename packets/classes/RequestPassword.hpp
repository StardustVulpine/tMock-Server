//
// Created by stardustvulpine on 1/17/26.
//

#pragma once
#include "BaseMessage.hpp"

namespace tmockserver::packets {
    class RequestPassword : public BaseMessage {
    public:
        RequestPassword();
        void Send(const networking::Socket &socket) const override;
    };
}
