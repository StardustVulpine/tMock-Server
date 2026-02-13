//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <memory>
#include "../include/PacketType.hpp"
#include <Socket.hpp>

// Base for every network packet

#define RESET_COLOR "\033[0m"
#define BLUE "\033[38;2;0;255;255m"
#define PURPLE "\033[38;2;255;0;255m"

namespace tmockserver::packets {
    class BasePacket {
    public:
        BasePacket(std::size_t size, PacketType type);

        virtual ~BasePacket() = default;

        void Print(std::optional<int> type) const;
        virtual void Send(const net::Socket &socket) const;

        [[nodiscard]] std::unique_ptr<std::byte[]> CreateBuffer() const;

        [[nodiscard]] short int GetPacketSize() const;

        /**
         * Calculates size of the base packet in bytes by summing byte size of two first fields: PacketSize and PacketType.
         * @return Byte size of the base packet
         */
        static constexpr std::size_t Size() {
            return sizeof(m_size) + sizeof(m_type);
        }

    private:
        short int m_size{}; // Field for storing size of entire packet using first two bytes
        std::byte m_type{}; // Type of the network packet

        [[nodiscard]] std::string GetPacketTypeNameAsString() const;

    };
} // tmockserver::messages