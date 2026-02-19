//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <memory>
#include "../include/PacketType.hpp"
#include <Socket.hpp>

// Base for every network packet
namespace tmockserver::packets {
    enum class PacketDirection
    {
        RECEIVE = 1,
        SEND
    };

    class BasePacket {
    public:
        BasePacket(std::size_t size, PacketType type);
        virtual ~BasePacket() = default;

        void PrintPacketHead(std::optional<PacketDirection> direction) const;
        virtual void Print() const = 0;

        void Send(const net::Socket &socket) const;

        //[[nodiscard]] virtual std::unique_ptr<std::byte[]> Serialize() const = 0;
        [[nodiscard]] virtual std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const = 0;
        [[nodiscard]] std::unique_ptr<std::byte[]> CreateBuffer() const;
        [[nodiscard]] short int GetPacketSize() const;

        /**
         * Calculates size of the base packet in bytes by summing byte size of two first fields: PacketSize and PacketType.
         * @return Byte size of the base packet
         */
        static constexpr std::size_t Size() {
            return sizeof(decltype(m_size)) + sizeof(decltype(m_type));
        }

    private:
        short int m_size{}; // Field for storing size of entire packet using first two bytes
        std::byte m_type{}; // Type of the network packet

        [[nodiscard]] std::string GetPacketTypeNameAsString() const;
    };

    template<typename T, typename S>
    requires std::is_enum_v<S>
    constexpr T enumTo (S type) {
        return static_cast<T>(type);
    }
} // tmockserver::messages