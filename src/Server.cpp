//
// Created by stardustvulpine on 2/10/26.
//

#include "Server.hpp"

#include <fstream>
#include <iostream>
#include <ostream>
#include <thread>
#include <json.hpp>
#include <mutex>
#include <Packets.hpp>

using json = nlohmann::json;

namespace
{
    template<typename T, typename... Args>
    auto createPacket(Args... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}

namespace tmockserver {
    Server::Server() : m_socket(net::Socket(net::AddressFamily::IPv4, net::ConnectionType::TCP))
    {
        m_config.password = "123";
    }

    void Server::Start()
    {
        m_socket.Bind(m_config.port);
        m_socket.Listen();
        std::println(std::cout, "{}Server started on port {}! {}", GREEN, m_config.port, RESET_COLOR);
        Run();
    }

    void Server::Run() {
        using namespace tmockserver::packets;
        using namespace tmockserver::net;
        using namespace tmockserver::terraria;

        // Initialize player list
        for (int i=0; i < m_config.max_players; i++) {
            m_player_list.emplace_back(static_cast<std::byte>(i));
        }

        std::println(std::cout, "{}Waiting for connections...{}", YELLOW, RESET_COLOR);

        //region Main loop
        while (true) {
            // Accept connection and assign move it to thread for handling
            Socket client_socket = m_socket.Accept();
            std::thread {[this, client_socket = std::move(client_socket)]() mutable
            {
                std::string clientIP = client_socket.GetAddressAsString(true);
                std::println(std::cout, "{}{} is connecting... {}", YELLOW, clientIP, RESET_COLOR);

                //region Assign socket to player if there free slot.
                Player *player = GetFreePlayer();
                if (!player) {
                    FatalError(NetworkTextMode::LITERAL, "Server is full.").Send(client_socket);
                    //Send(client_socket, createPacket<FatalError>(NetworkTextMode::LITERAL, "Server is full."));
                    return;
                }
                player->SetSocket(std::move(client_socket));
                //endregion

                // Client-Server communication loop
                bool connected = true;
                while (connected) {

                    // Buffer for catching message's head to determine it's size and type
                    auto msgBuffer = std::make_unique<std::byte[]>(BasePacket::Size());
                    player->GetSocket().Read(msgBuffer.get(), BasePacket::Size());
                    const short int msgSize = *reinterpret_cast<short int *>(msgBuffer.get());

                    // Based on message type received from client, route to catch rest of the message content.
                    std::byte msgType = *(msgBuffer.get() + sizeof(decltype(msgSize)));

                    switch ( static_cast<PacketType>(msgType)) {
                        case PacketType::CONNECT_REQUEST:
                        {
                            if (ConnectRequest connect_request (msgSize, msgBuffer, player->GetSocket()); connect_request.GetClientVersion() != m_serverVersion) {
                                FatalError(NetworkTextMode::LITERAL, "Server doesn't support this version of game.").Send(player->GetSocket());
                                connected = false;
                                break;
                            }

                            if (m_config.password) {
                                RequestPassword().Send(player->GetSocket());
                                break;
                            }

                            std::println(std::cout, "{}{} connection approved. {}", GREEN, clientIP, RESET_COLOR);
                            ConnectionApproved(player->GetID()).Send(player->GetSocket());
                            break;
                        }
                        case PacketType::RECEIVE_PASSWORD:
                        {
                            if (SendPassword recPass (msgSize, msgBuffer, player->GetSocket()); recPass.Content() != m_config.password) {
                                FatalError(NetworkTextMode::LITERAL, "Wrong password.").Send(player->GetSocket());
                                connected = false;
                                break;
                            }
                            ConnectionApproved(player->GetID()).Send(player->GetSocket());
                            break;
                        }

                        default:
                            // Consume the rest of the packet to keep stream in sync
                            auto buffer = std::make_unique<std::byte[]>(msgSize - BasePacket::Size());
                            player->GetSocket().Read(buffer.get(), msgSize - BasePacket::Size());

                            std::println(std::cout, "{}{} has send unhandled message type: {}{}",
                                RED, player->GetSocket().GetAddressAsString(), static_cast<int>(msgType), RESET_COLOR
                            );
                            //FatalError(NetworkTextMode::LITERAL, "Unhandled message type.").Send(player->GetSocket());
                            //connected = false;
                    }
                }
                std::println(std::cout, "{}{} disconnected {}", YELLOW, clientIP, RESET_COLOR);
            }}.detach();
        } //endregion Main loop
    } // Run

    std::vector<terraria::Player> &Server::PlayerList() { return m_player_list;}

    terraria::Player *Server::GetFreePlayer()
    {
        std::scoped_lock lock(m_GetFreePlayerMutex);
        for (auto &player : m_player_list) {
            if (!player.GetSocket().IsConnected()) {
                return &player;
            }
        }
        return nullptr;
    }

    /*void Server::Send(const net::Socket &socket, std::unique_ptr<packets::BasePacket> packet)
    {
        socket.Write(packet->Serialize(), packet->GetPacketSize());
    }*/
} // tmockserver