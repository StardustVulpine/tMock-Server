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
#include "Colors.hpp"

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

    [[noreturn]]
    void Server::Run()
    {
        m_config.password = "dupa";

        using namespace tmockserver::packets;
        using namespace tmockserver::networking;

        std::vector<std::thread> connected_clients;

        while (true)
        {
            Socket client_socket = m_socket.Accept();
            if (connected_clients.size() == static_cast<unsigned long>(m_config.max_clients))
            {

            }

            std::thread client_thread {[client = std::move(client_socket), this]()
            {
                std::string clientIP = client.GetAddress();
                std::println(std::cout, "{}{} is connecting... {}", YELLOW, clientIP, RESET_COLOR);
                bool done = false;
                while (!done) {

                    // Buffer for catching message's head to determine it's size and type
                    auto msgBuffer = std::make_unique<std::byte[]>(BasePacket::Size());
                    client.Read(msgBuffer.get(), BasePacket::Size());
                    const short int msgSize = *reinterpret_cast<short int *>(msgBuffer.get());
                    std::byte msgType = *(msgBuffer.get() + sizeof(msgSize));

                    // Based on message type received from client, route to catch rest of the message content.
                    switch (static_cast<PacketType>(msgType)) {
                        case PacketType::CONNECT_REQUEST:
                        {
                            ConnectRequest connect_request (msgSize, msgBuffer, client);
                            connect_request.Print();

                            if (connect_request.GetClientVersion() != m_serverVersion) {
                                FatalError(NetworkTextMode::LITERAL, "Server doesn't support this version of game.").Send(client);
                                done = true;
                                break;
                            }

                            if (m_config.password) {
                                RequestPassword().Send(client);
                                break;
                            }

                            std::println(std::cout, "{}{} connection approved. {}", GREEN, clientIP, RESET_COLOR);
                            ConnectionApproved(1).Send(client);
                            break;
                        }
                        case PacketType::RECEIVE_PASSWORD:
                        {
                            SendPassword recPass (msgSize, msgBuffer, client);
                            recPass.Print();

                            if (recPass.Content() != m_config.password) {
                                FatalError(NetworkTextMode::LITERAL, "Wrong password.").Send(client);
                                done = true;
                                break;
                            }

                            ConnectionApproved(1).Send(client);
                            break;
                        }
                        default:
                            std::println(std::cout, "{}Unhandled message type received from {} {}", RED, client.GetAddress(), RESET_COLOR);
                            FatalError(NetworkTextMode::LITERAL, "Unhandled message type received from client.").Send(client);
                            done = true;
                            break;
                    }
                }
                std::println(std::cout, "{}{} disconnected. {}", YELLOW, clientIP, RESET_COLOR);
            }};
            connected_clients.emplace_back(std::move(client_thread));
            //std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
} // tmockserver