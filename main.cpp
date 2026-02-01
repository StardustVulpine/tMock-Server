#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <vector>
#include <Socket.hpp>
#include <Packets.hpp>
#include "extern_lib/json.hpp"

using json = nlohmann::json;

json load_server_config();

[[noreturn]]
int main()
{
    using namespace tmockserver;
    using namespace tmockserver::packets;
    using namespace tmockserver::networking;

    json server_config = load_server_config();
    auto server_version = server_config["server_version"].get<int>();
    auto port = server_config["port"].get<int>();
    auto max_clients = server_config["max_clients"].get<unsigned>();
    auto password = server_config["password"].get<std::string>();

    Socket server_socket(AddressFamily::IPv4, ConnectionType::TCP);
    server_socket.Bind(port);
    server_socket.Listen();
    std::println(std::cout, "\033[38;2;0;255;1m {} \033[0m", "Server Started!");
    std::println(std::cout, "\033[38;2;255;250;115m {} {}\033[0m", "Listening on port:", port);

    std::vector<std::thread> connected_clients;

    while (true) {
        std::println(std::cout, "Connected clients: {}", connected_clients.size());
        std::println(std::cout, "Awaiting client connection...");

        Socket client_socket = server_socket.Accept();
        if (connected_clients.size() == max_clients)
        {

        }

        std::thread client_thread {[client = std::move(client_socket), password, server_version]()
        {
            std::println(std::cout, "\033[38;2;0;255;0m {} {} \033[0m", "Client connected from", client.GetAddress());
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
                        if (connect_request.GetClientVersion() != server_version) {
                            FatalError(NetworkTextMode::LITERAL, "Server doesn't support this version of game.").Send(client);
                            done = true;
                            break;
                        }
                        if (!password.empty()) {
                            RequestPassword().Send(client);
                            break;
                        }
                        ConnectionApproved(1).Send(client);
                        break;
                    }
                    case PacketType::RECEIVE_PASSWORD:
                    {
                        SendPassword recPass (msgSize, msgBuffer, client);
                        recPass.Print();
                        if (recPass.Content() != password) {
                            FatalError(NetworkTextMode::LITERAL, "Tybijskie hasło").Send(client);
                            done = true;
                            break;
                        }
                        ConnectionApproved(1).Send(client);
                        break;
                    }
                    default:
                        std::println(std::cout, "Unhandled message type received from client.");
                        FatalError(NetworkTextMode::LITERAL, "Unhandled message type received from client.").Send(client);
                        break;
                }
            }
        }};
        connected_clients.emplace_back(std::move(client_thread));
        //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}

json load_server_config() {
    std::ifstream fs("server-config.json");
    return json::parse(fs);

}