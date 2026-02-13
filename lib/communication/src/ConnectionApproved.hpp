//
// Created by stardustvulpine on 2/1/26.
//

#pragma once

#include <cstddef>
#include "BasePacket.hpp"

namespace tmockserver::packets {
    class ConnectionApproved : public BasePacket {
    public:
        explicit ConnectionApproved(std::byte playerSlotID);
        ~ConnectionApproved() override = default;

        void Print() const ;
        void Send(const net::Socket &socket) const override;

    private:
        std::byte m_playerSlotID{};
    };
}
