//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <memory>

#include "../enums/PacketType.hpp"

#include <Socket.hpp>

namespace tmockserver::packets {
    class BasePacket {
    public:
        BasePacket(std::size_t size, PacketType type);


        virtual ~BasePacket() = default;

        virtual void Print() const;
        virtual void Send(const networking::Socket &socket) const;

        [[nodiscard]] std::unique_ptr<std::byte[]> CreateBuffer() const;

        static constexpr std::size_t Size() {
            return sizeof(m_size) + sizeof(m_type);
        }
    private:
        short int m_size{};
        std::byte m_type{};

        std::string GetMessageTypeName() const;

    };
} // tmockserver::messages