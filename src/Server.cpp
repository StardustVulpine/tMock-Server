//
// Created by stardustvulpine on 2/10/26.
//

#include "Server.hpp"

#include <fstream>
#include <iostream>
#include <ostream>
#include <thread>
#include <json.hpp>
#include <Packets.hpp>

using json = nlohmann::json;

namespace tmockserver {
    Server::Server() : m_socket(Socket(AddressFamily::IPv4, ConnectionType::TCP)){}

    void Server::Start()
    {
        m_socket.Bind(m_config.port);
        m_socket.Listen();
        std::println(std::cout, "{}Server started on port {}! {}", GREEN, m_config.port, RESET_COLOR);
        Run();
    }

    void Server::Run() {
        using namespace tmockserver::packets;
        using namespace tmockserver::networking;
        using namespace tmockserver::gamestate;

        m_config.password = "123";

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
                std::string clientIP = client_socket.GetAddress(true);
                std::println(std::cout, "{}{} is connecting... {}", YELLOW, clientIP, RESET_COLOR);

                //region Assign socket to player if there free slot.
                Player *player = GetFreePlayer();
                if (!player) {
                    FatalError(NetworkTextMode::LITERAL, "Server is full.").Send(client_socket);
                    return;
                }
                player->SetSocket(std::move(client_socket));
                //endregion

                // Client - Server communication loop
                bool connected = true;
                while (connected) {

                    // Buffer for catching message's head to determine it's size and type
                    auto msgBuffer = std::make_unique<std::byte[]>(BasePacket::Size());
                    player->GetSocket().Read(msgBuffer.get(), BasePacket::Size());
                    const short int msgSize = *reinterpret_cast<short int *>(msgBuffer.get());

                    // Based on message type received from client, route to catch rest of the message content.
                    switch (std::byte msgType = *(msgBuffer.get() + sizeof(msgSize)); static_cast<PacketType>(msgType)) {
                        case PacketType::CONNECT_REQUEST:
                        {
                            ConnectRequest connect_request (msgSize, msgBuffer, player->GetSocket());
                            connect_request.Print();

                            if (connect_request.GetClientVersion() != m_serverVersion) {
                                FatalError(NetworkTextMode::LITERAL, "Server doesn't support this version of game.").Send(player->GetSocket());
                                connected = false;
                                break;
                            }

                            if (m_config.password) {
                                RequestPassword().Send(player->GetSocket());
                                break;
                            }

                            std::println(std::cout, "{}{} connection approved. {}", GREEN, clientIP, RESET_COLOR);
                            ConnectionApproved(1).Send(player->GetSocket());
                            break;
                        }
                        case PacketType::RECEIVE_PASSWORD:
                        {
                            SendPassword recPass (msgSize, msgBuffer, player->GetSocket());
                            recPass.Print();

                            if (recPass.Content() != m_config.password) {
                                FatalError(NetworkTextMode::LITERAL, "Wrong password.").Send(player->GetSocket());
                                connected = false;
                                break;
                            }

                            ConnectionApproved(1).Send(player->GetSocket());
                            break;
                        }
                        default:
                            std::println(std::cout, "{}{} has send unhandled message type: {}{}",
                                RED, player->GetSocket().GetAddress(), static_cast<int>(msgType), RESET_COLOR
                            );
                            FatalError(NetworkTextMode::LITERAL, "Unhandled message type.").Send(player->GetSocket());
                            connected = false;
                            break;
                    }
                }
                std::println(std::cout, "{}{} disconnected {}", YELLOW, clientIP, RESET_COLOR);
            }}.detach();
        } //endregion Main loop
    } // Run

    std::vector<Player> &Server::PlayerList() { return m_player_list;}
    Player *Server::GetFreePlayer()
    {
        for (auto &player : m_player_list) {
            if (!player.GetSocket().IsConnected()) {
                return &player;
            }
        }
        return nullptr;
    }
} // tmockserver