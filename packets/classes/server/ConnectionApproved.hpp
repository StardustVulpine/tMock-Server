//
// Created by stardustvulpine on 2/1/26.
//

#pragma once
#include <cstddef>

#include "../BasePacket.hpp"

namespace tmockserver::packets {
    class ConnectionApproved : public BasePacket {
    public:
        explicit ConnectionApproved(int playerSlotID);
        ~ConnectionApproved() override = default;

        void Print() const override;
        void Send(const networking::Socket &socket) const override;

    private:
        std::byte m_playerSlotID{};
    };
}
