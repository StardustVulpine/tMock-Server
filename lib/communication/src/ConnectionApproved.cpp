//
// Created by stardustvulpine on 2/1/26.
//

#include "ConnectionApproved.hpp"
#include <iostream>
#include "Exception.hpp"

namespace tmockserver::packets {
    ConnectionApproved::ConnectionApproved(const std::byte playerSlotID)
    : BasePacket(Size()+sizeof(m_playerSlotID), PacketType::CONNECTION_APPROVED),
    m_playerSlotID(static_cast<std::byte>(playerSlotID)) {

    }

    void ConnectionApproved::Print() const {
        BasePacket::Print(1);
        std::println(std::cout, "  [PAYLOAD] Player Slot: {}", std::to_integer<int>(m_playerSlotID));
    }

    void ConnectionApproved::Send(const net::Socket &socket) const {
        try {
            const auto buffer = CreateBuffer();
            std::byte* ptr = buffer.get();
            ptr += Size();
            *ptr++ = m_playerSlotID;
            (void)ptr; // :C

            Print();
            socket.Write(buffer.get(), Size()+sizeof(std::byte));
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
