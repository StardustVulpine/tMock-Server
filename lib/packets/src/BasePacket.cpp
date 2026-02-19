//
// Created by stardustvulpine on 1/11/26.
//

#include "BasePacket.hpp"
#include <iostream>

#include "Exception.hpp"

// Base for every network packet
namespace tmockserver::packets {

#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[38;2;0;255;255m"
#define COLOR_PURPLE "\033[38;2;255;0;255m"

    /**
     * Create base network packet by defining its size and type. Can be extended when inherited by other classes.
     * @param size Size of the packet
     * @param type Type of network packet
     */
    BasePacket::BasePacket(const std::size_t size, const PacketType type) {
        m_size = static_cast<short int>(size);
        m_type = enumTo<std::byte>(type);
    }

    /**
     * Print packet's head to console with flag determining direction of packet.
     * @param direction Direction of packet from enum. PacketDirection::RECEIVE if receiving packet or PacketDirection::SEND if sending.
     */
    void BasePacket::PrintPacketHead(const std::optional<PacketDirection> direction) const {
        if (direction == PacketDirection::RECEIVE) { //received packet
            std::println(std::cout, "{} <- [PACKET RECEIVED]{} Size: {}, Type: ({}){}", COLOR_BLUE, COLOR_RESET, m_size, static_cast<int>(m_type), GetPacketTypeNameAsString());
            return;
        }
        if (direction == PacketDirection::SEND) { // send packet
            std::println(std::cout, "{} -> [PACKET SEND]{} Size: {}, Type: ({}){}", COLOR_PURPLE, COLOR_RESET, m_size, static_cast<int>(m_type), GetPacketTypeNameAsString());
            return;
        }
    }

    void BasePacket::Send(const net::Socket &socket [[maybe_unused]]) const {
        try {
            const auto buffer = GetPacketContent(CreateBuffer());
            Print();
            socket.Write(buffer.get(), m_size);
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    /**
     * Creates byte buffer with three first bytes already filled with packet size data' and it's type.
     * @return Byte buffer for further sending.
     */
    std::unique_ptr<std::byte[]> BasePacket::CreateBuffer() const {
        auto buffer = std::make_unique<std::byte[]>(m_size);
        std::byte* ptr = buffer.get();

        *reinterpret_cast<short int*>(ptr) = m_size;
        ptr += sizeof(m_size);
        *ptr = enumTo<std::byte>(m_type);

        return buffer;
    }

    /**
     * @return Size of packet read from two first bytes of packet data
     */
    short int BasePacket::GetPacketSize() const {
        return m_size;
    }


    /**
     * @return Packet type name as string
     */
    std::string BasePacket::GetPacketTypeNameAsString() const {
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
                name = "UNKNOWN_PACKET_NAME";
                break;
        }

        return name;
    }
} // tmockserver::messages