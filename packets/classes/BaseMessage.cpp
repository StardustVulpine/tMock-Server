//
// Created by stardustvulpine on 1/11/26.
//

#include "BaseMessage.hpp"

#include <iostream>
#include <sstream>

#include "../enums/NetworkTextMode.hpp"

namespace tmockserver::packets {

    BaseMessage::BaseMessage(const std::size_t size, const PacketType type) {
        m_size = static_cast<short int>(size);
        m_type = enumTo<std::byte>(type);
    }

    void BaseMessage::Print() const {
        std::println(std::cout, "Message Size: {}", m_size);
        std::println(std::cout, "Message Type: {}", static_cast<int>(m_type));
    }

    void BaseMessage::Send(const networking::Socket &socket [[maybe_unused]]) const {

    }

    std::unique_ptr<char[]> BaseMessage::CreateBuffer() const {
        auto buffer = std::make_unique<char[]>(m_size);
        char* ptr = buffer.get();

        *reinterpret_cast<short int*>(ptr) = m_size;
        ptr += sizeof(m_size);
        *ptr = enumTo<char>(m_type);
        return buffer;
    }
} // tmockserver::messages