//
// Created by stardustvulpine on 1/17/26.
//

#include "RequestPassword.hpp"
#include <iostream>
#include "../enums/PacketType.hpp"
#include <Exception.hpp>

namespace tmockserver::packets {
    RequestPassword::RequestPassword() : BasePacket(3, PacketType::REQUEST_PASSWORD){}

    void RequestPassword::Print() const {
        BasePacket::Print(1);
        std::println(std::cout, "  [NO-PAYLOAD]");
    }

    void RequestPassword::Send(const networking::Socket &socket) const {
        try {
            const auto buffer = CreateBuffer();
            Print();
            socket.Write(buffer.get(), Size());
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

