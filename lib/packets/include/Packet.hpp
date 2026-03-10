//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <memory>
#include <type_traits>
#include <cstddef>
#include <Socket.hpp>
#include <iostream>
//#include "../../../src/Log.hpp"

// Base for every network packet
namespace tmockserver::packets {
    enum class PacketType : std::underlying_type_t<std::byte>;

    class Packet {
        public:
        enum class Direction
        {
            INCOMING = 1,
            OUTGOING
        };

        Packet(std::size_t size, PacketType type);
        virtual ~Packet() = default;

        void PrintPacketHead(std::optional<Direction> direction) const;
        [[nodiscard]] std::string GetPacketHeadAsString(Direction direction) const;

        virtual void Print() const = 0;

        void Send(const net::Socket &socket) const;

        //[[nodiscard]] virtual std::unique_ptr<std::byte[]> Serialize() const = 0;
        [[nodiscard]] virtual std::unique_ptr<std::byte[]> GetPacketContent(std::unique_ptr<std::byte[]> buffer) const = 0;
        [[nodiscard]] std::unique_ptr<std::byte[]> CreateBuffer() const;

        /**
         * Calculates size of the base packet in bytes by summing byte size of two first fields: PacketSize and PacketType.
         * @return Byte size of the base packet
         */
        static constexpr std::size_t PacketHeadSize() {
            return sizeof(decltype(m_size)) + sizeof(decltype(m_type));
        }
        [[nodiscard]] short int PacketSize() const;

        private:
        short int m_size{}; // Field for storing size of entire packet using first two bytes
        std::byte m_type{}; // Type of the network packet
        //std::unique_ptr<std::byte[]> m_buffer;

        [[nodiscard]] std::string GetPacketTypeNameAsString() const;
    };

    template<typename T, typename S>
    requires std::is_enum_v<S>
    constexpr T enumTo (S type) {
        return static_cast<T>(type);
    }

    enum class PacketType : std::underlying_type_t<std::byte> {
        CONNECT_REQUEST = 0x01,          // Client -> Server
        FATAL_ERROR = 0x02,              // Server -> Client
        CONNECTION_APPROVED = 0x03,      // Server -> Client
        PLAYER_INFO = 0x04,

        /* Some other messages here will be added later */

        REQUEST_PASSWORD = 0x25,        // Server -> Client
        RECEIVE_PASSWORD = 0x26,     // Client -> Server

        CLIENT_UUID = 0x68
    };

    enum class NetworkTextMode : std::underlying_type_t<std::byte> {
        LITERAL = 0x00,
        FORMATTABLE = 0x01,
        LOCALIZATION_KEY = 0x02,
        SUBSTITUTION = 0x03,
    };
} // tmockserver::messages