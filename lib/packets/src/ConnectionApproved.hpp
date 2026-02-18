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

        void Print() const override;
        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const override;

    private:
        std::byte m_playerSlotID{};
    };
}
