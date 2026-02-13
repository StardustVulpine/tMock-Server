//
// Created by stardustvulpine on 1/11/26.
//

#include "BasePacket.hpp"
#include <iostream>

#include "Exception.hpp"
#include "../include/NetworkTextMode.hpp"

// Base for every network packet
namespace tmockserver::packets {

    /**
     * Create base network packet by defining its size and type. Can be extended when inherited by other classes.
     * @param size Size of the packet
     * @param type Type of network packet
     */
    BasePacket::BasePacket(const std::size_t size, const PacketType type) {
        m_size = static_cast<short int>(size);
        m_type = enumTo<std::byte>(type);
    }

    /* Logging method used for printing packet details in server console for debugging purposes
     */
    void BasePacket::Print(const std::optional<int> type) const {
        if (type == 0) { //received packet
            std::println(std::cout, "{}> [PACKET RECEIVED]{} Size: {}, Type: ({}){}", BLUE, RESET_COLOR, m_size, static_cast<int>(m_type), GetPacketTypeNameAsString());
        }
        if (type == 1) { // send packet
            std::println(std::cout, "{}> [PACKET SEND]{} Size: {}, Type: ({}){}", PURPLE, RESET_COLOR, m_size, static_cast<int>(m_type), GetPacketTypeNameAsString());
        }
    }

    void BasePacket::Send(const net::Socket &socket [[maybe_unused]]) const {
        /*try {
            auto [buffer, size] = GetContent();
            Print();
            socket.Write(buffer.get(), size);
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }*/
    }

    /**
     * Creates byte buffer with three first bytes already filled with packet size data and it's type.
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
     *
     * @return Size of packet read from two first bytes of packet data
     */
    short int BasePacket::GetPacketSize() const {
        return m_size;
    }


    /**
     * 
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
                break;
        }

        return name;
    }
} // tmockserver::messages