#include <iostream>
#include <memory>
#include "TextModes.h"
#include "classes/Socket.hpp"
#include "classes/Messages.hpp"
#include <thread>
#include <vector>

constexpr int SERVER_PORT = 8090;
constexpr int MAX_ALLOWED_CLIENTS = 3;
constexpr std::string SERVER_PASSWORD = "dupa";

[[noreturn]]
int main()
{
    using namespace tmockserver;
    using namespace tmockserver::messages;

    Socket server_socket(AddressFamily::IPv4, ConnectionType::TCP);
    server_socket.Bind(SERVER_PORT);
    server_socket.Listen();
    std::println(std::cout, "\033[38;2;0;255;1m {} \033[0m", "Server Started!");
    std::println(std::cout, "\033[38;2;255;250;115m {} {}\033[0m", "Listening on port:", SERVER_PORT);

    std::vector<std::thread> connected_clients;

    while (true) {
        std::println(std::cout, "Connected clients: {}", connected_clients.size());
        std::println(std::cout, "Awaiting client connection...");

        Socket client_socket = server_socket.Accept();
        if (connected_clients.size() == MAX_ALLOWED_CLIENTS)
        {

        }

        std::thread client_thread {[client = std::move(client_socket), &connected_clients]()
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
                switch (static_cast<MessageTypes>(msgType)) {
                    case MessageTypes::CONNECT_REQUEST:
                    {
                        std::println(std::cout, "Client requested connection with message details:");
                        ConnectRequest(msgSize, msgBuffer, client).Print();
                        RequestPasswordMessage().Send(client);
                        break;
                    }
                    case MessageTypes::RECEIVE_PASSWORD:
                    {
                        std::println(std::cout, "Client sent password.");
                        RecievePasswordMessage recPass (msgSize, msgBuffer, client);
                        recPass.Print();
                        if (recPass.Content() != SERVER_PASSWORD) {
                            FatalErrorMessage(TextModes::LITERAL, "Tybijskie hasło").Send(client);
                            done = true;
                            break;
                        }
                        FatalErrorMessage(TextModes::LITERAL, "Hello tMockServer!").Send(client);
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