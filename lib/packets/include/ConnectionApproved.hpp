//
// Created by stardustvulpine on 2/1/26.
//

#pragma once

#include "Packet.hpp"

namespace tmockserver::packets {
    class ConnectionApproved : public Packet {
    public:
        explicit ConnectionApproved(const std::byte playerSlotID) : Packet(PacketHeadSize()+sizeof(m_playerSlotID), PacketType::CONNECTION_APPROVED), m_playerSlotID(playerSlotID) {}
        ~ConnectionApproved() override = default;

        void Print() const override {
            PrintPacketHead(Direction::OUTGOING);
            std::println(std::cout, "  [PAYLOAD] Player Slot: {}", std::to_integer<int>(m_playerSlotID));
        }
        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const override
        {
            std::byte* ptr = buffer.get();
            ptr += PacketHeadSize();
            *ptr++ = m_playerSlotID;
            (void)ptr; // :C

            return buffer;
        }

    private:
        std::byte m_playerSlotID{};
    };
}
