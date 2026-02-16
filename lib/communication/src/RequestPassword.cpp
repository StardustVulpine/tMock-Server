//
// Created by stardustvulpine on 1/17/26.
//

#include "RequestPassword.hpp"
#include <iostream>
#include "../include/PacketType.hpp"
#include <Exception.hpp>

namespace tmockserver::packets {
    RequestPassword::RequestPassword() : BasePacket(3, PacketType::REQUEST_PASSWORD){}

    void RequestPassword::Print() const {
        BasePacket::PrintPacketHead(1);
        std::println(std::cout, "  [NO-PAYLOAD]");
    }

    std::unique_ptr<std::byte[]> RequestPassword::GetPacketContent(std::unique_ptr<std::byte[]> buffer) const
    {
        return buffer;
    }
}

