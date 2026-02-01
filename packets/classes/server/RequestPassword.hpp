//
// Created by stardustvulpine on 1/17/26.
//

#pragma once

#include "../BasePacket.hpp"

namespace tmockserver::packets {
    class RequestPassword : public BasePacket {
    public:
        RequestPassword();
        void Print() const override;
        void Send(const networking::Socket &socket) const override;
    };
}
