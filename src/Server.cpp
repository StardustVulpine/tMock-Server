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
#include <TNPPackets.hpp>
#include "Log.hpp"

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
        Console::Log::Info("Server started on port {}!", m_config.port);
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
        Console::Log::Info("Waiting for connections...");

        std::thread {[this](){
            ConsoleLoop();
        }}.detach();

        //region Main loop
        while (true) {
            // Accept connection and assign move it to thread for handling
            Socket client_socket = m_socket.Accept();
            if (!client_socket.IsConnected()) break;

            std::thread {[this, client_socket = std::move(client_socket)]() mutable
            {
                std::string clientIP = client_socket.GetAddressAsString(true);
                Console::Log::Warning("{} is connecting...", clientIP);

                //region Assign socket to player if there free slot.
                Player *player = GetFreePlayer();
                if (!player) {
                    FatalError(NetworkTextMode::LITERAL, "Server is full.").Send(client_socket);
                    return;
                }
                player->SetSocket(std::move(client_socket));
                //endregion

                // Client-Server communication loop
                bool connected = true;
                while (connected) {

                    // Buffer for catching message's head to determine it's size and type
                    auto packetBuffer = std::make_unique<std::byte[]>(Packet::PacketHeadSize());
                    player->GetSocket().Read(packetBuffer.get(), Packet::PacketHeadSize());
                    const short int packetSize = *reinterpret_cast<short int *>(packetBuffer.get());

                    // Based on message type received from client, route to catch rest of the message content.
                    std::byte msgType = *(packetBuffer.get() + sizeof(decltype(packetSize)));

                    switch ( static_cast<PacketType>(msgType)) {
                        case PacketType::CONNECT_REQUEST:
                        {
                            if (ConnectRequest connect_request (packetSize, packetBuffer, player->GetSocket()); connect_request.GetClientVersion() != m_serverVersion) {
                                connected = Disconnect(player, "Server doesn't support this version of game.");
                                break;
                            }

                            if (m_config.password) {
                                RequestPassword().Send(player->GetSocket());
                                break;
                            }

                            Console::Log::Info("{} connection approved.", clientIP);
                            ConnectionApproved(player->GetID()).Send(player->GetSocket());
                            break;
                        }
                        case PacketType::RECEIVE_PASSWORD:
                        {
                            if (SendPassword recPass (packetSize, packetBuffer, player->GetSocket()); recPass.Content() != m_config.password) {
                                connected = Disconnect(player, "Wrong password.");
                                break;
                            }
                            ConnectionApproved(player->GetID()).Send(player->GetSocket());
                            break;
                        }

                        default:
                            // Consume the rest of the packet to keep network data stream in sync
                            auto buffer = std::make_unique<std::byte[]>(packetSize - Packet::PacketHeadSize());
                            player->GetSocket().Read(buffer.get(), packetSize - Packet::PacketHeadSize());

                            Console::Log::Error("{} has send unhandled message type: {}", clientIP, static_cast<int>(msgType));
                            //connected = Disconnect(player, "Unhandled message type.");
                    }
                }
                Console::Log::Warning("{} disconnected", clientIP);
            }}.detach();
        } //endregion Main loop

    } // Run

    void Server::ConsoleLoop() {
        std::string input;
        while (true) {
            std::getline(std::cin, input);
            const auto pos = input.find(' ');
            std::string command = input.substr(0, pos);
            std::string args = input.substr(pos + 1);


            if (command == "ping")
            {
                Console::Log::Print("Pong!");
            }
            else if (command == "show")
            {
                if (args == "port") {
                    Console::Log::Print("Server port: {}", m_config.port);
                } else if (args == "ip")
                {
                    Console::Log::Print("Server IP: {}", m_socket.GetAddressAsString());
                } else
                {
                    Console::Log::Error("Missing or unknown arguments!");
                    Console::Log::Print("Available arguments:\n"
                        "                              port - prints server port\n"
                        "                              ip - prints server ip");
                }
            }
            else if (command == "exit")
            {
                Console::Log::Warning("Shutting down server...");
                exit(0);
            } else {
                Console::Log::Error("Unknow command!");
                Console::Log::Print("Available commands:\n"
                        "                              ping - replies with pong\n"
                        "                              show <ip/port> - print server port or ip depending on provided argument\n"
                        "                              exit - shuts down server\n");
            }
        }
    } // ConsoleLoop

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

    bool Server::Disconnect(terraria::Player *player, const std::string& reason)
    {
        packets::FatalError(packets::NetworkTextMode::LITERAL, reason).Send(player->GetSocket());
        return false;
    }

    /*void Server::Send(const net::Socket &socket, std::unique_ptr<packets::BasePacket> packet)
    {
        socket.Write(packet->Serialize(), packet->GetPacketSize());
    }*/
} // tmockserver