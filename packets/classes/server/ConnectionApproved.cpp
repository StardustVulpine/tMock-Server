//
// Created by stardustvulpine on 2/1/26.
//

#include "ConnectionApproved.hpp"

#include <iostream>

#include "Exception.hpp"

namespace tmockserver::packets {
    ConnectionApproved::ConnectionApproved(const int playerSlotID)
    : BasePacket(Size()+sizeof(m_playerSlotID), PacketType::CONNECTION_APPROVED),
    m_playerSlotID(static_cast<std::byte>(playerSlotID)) {

    }

    void ConnectionApproved::Print() const {
        std::println(std::cout, "\033[38;2;0;255;1m Client Connection Approved. \033[0m");
        BasePacket::Print();
        std::println(std::cout, "Player Slot: {}", std::to_integer<int>(m_playerSlotID));
    }

    void ConnectionApproved::Send(const networking::Socket &socket) const {
        try {
            const auto buffer = CreateBuffer();
            std::byte* ptr = buffer.get();
            ptr += Size();
            *ptr++ = m_playerSlotID;
            (void)ptr; // :C

            Print();
            socket.Write(buffer.get(), Size()+sizeof(m_playerSlotID));
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
