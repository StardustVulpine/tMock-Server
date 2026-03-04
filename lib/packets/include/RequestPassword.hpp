//
// Created by stardustvulpine on 1/17/26.
//

#pragma once

#include "Packet.hpp"

namespace tmockserver::packets {
    class RequestPassword : public Packet {
    public:
        RequestPassword() : Packet(PacketHeadSize(), PacketType::REQUEST_PASSWORD){}
        void Print() const override {
            PrintPacketHead(Direction::OUTGOING);
            std::println(std::cout, "  [NO-PAYLOAD]");
        }
        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const override
        {
            return buffer;
        }
    };
}
