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

        std::thread client_thread {[client = std::move(client_socket), password]()
        {
            bool done = false;
            while (!done) {
                std::println(std::cout, "\033[38;2;0;255;0m {} {} \033[0m", "Client connected from", client.GetAddress());

                // Buffer for catching message's head to determine it's size and type
                auto msgBuffer = std::make_unique<std::byte[]>(BaseMessage::Size());
                client.Read(msgBuffer.get(), BaseMessage::Size());
                const short int msgSize = *reinterpret_cast<short int *>(msgBuffer.get());
                std::byte msgType = *(msgBuffer.get() + sizeof(msgSize));

                // Based on message type received from client, route to catch rest of the message content.
                switch (static_cast<PacketType>(msgType)) {
                    case PacketType::CONNECT_REQUEST:
                    {
                        std::println(std::cout, "Client requested connection.");
                        ConnectRequest(msgSize, msgBuffer, client).Print();
                        RequestPassword().Send(client);
                        break;
                    }
                    case PacketType::RECEIVE_PASSWORD:
                    {
                        std::println(std::cout, "Client sent password.");
                        SendPassword recPass (msgSize, msgBuffer, client);
                        recPass.Print();
                        if (recPass.Content() != password) {
                            FatalError(NetworkTextMode::LITERAL, "Tybijskie hasło").Send(client);
                            done = true;
                            break;
                        }
                        FatalError(NetworkTextMode::LITERAL, "Hello tMockServer!").Send(client);
                        done = true;
                        break;
                    }
                    default:
                        std::println(std::cout, "Unhandled message type received from client.");
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