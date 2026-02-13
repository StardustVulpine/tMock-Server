//
// Created by stardustvulpine on 1/17/26.
//

#pragma once

#include "BasePacket.hpp"

namespace tmockserver::packets {
    class RequestPassword : public BasePacket {
    public:
        RequestPassword();
        void Print() const;
        void Send(const net::Socket &socket) const override;
    };
}
