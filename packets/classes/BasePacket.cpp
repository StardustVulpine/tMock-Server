//
// Created by stardustvulpine on 1/11/26.
//

#include "BasePacket.hpp"

#include <iostream>
#include <sstream>

#include "../enums/NetworkTextMode.hpp"

namespace tmockserver::packets {

    BasePacket::BasePacket(const std::size_t size, const PacketType type) {
        m_size = static_cast<short int>(size);
        m_type = enumTo<std::byte>(type);
    }

    void BasePacket::Print() const {
        std::println(std::cout, "Message Size: {}", m_size);
        std::println(std::cout, "Message Type: {}, {}", static_cast<int>(m_type), GetMessageTypeName());
    }

    void BasePacket::Send(const networking::Socket &socket [[maybe_unused]]) const {

    }

    std::unique_ptr<std::byte[]> BasePacket::CreateBuffer() const {
        auto buffer = std::make_unique<std::byte[]>(m_size);
        std::byte* ptr = buffer.get();

        *reinterpret_cast<short int*>(ptr) = m_size;
        ptr += sizeof(m_size);
        *ptr = enumTo<std::byte>(m_type);
        return buffer;
    }

    std::string BasePacket::GetMessageTypeName() const {
        std::string name;

        switch(static_cast<PacketType>(m_type)) {
            case PacketType::CONNECT_REQUEST:
                name = "CONNECT_REQUEST";
                break;
            case PacketType::FATAL_ERROR:
                name = "FATAL_ERROR";
                break;
            case PacketType::CONNECTION_APPROVED:
                name = "CONNECTION_APPROVED";
                break;
            case PacketType::REQUEST_PASSWORD:
                name = "REQUEST_PASSWORD";
                break;
            case PacketType::RECEIVE_PASSWORD:
                name = "RECEIVE_PASSWORD";
                break;
            default:
                break;
        }

        return name;
    }
} // tmockserver::messages