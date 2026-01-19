#include <iostream>
#include <memory>

#include "Exception.hpp"
#include "TextModes.h"
#include "classes/Socket.hpp"
#include "classes/Log.hpp"
#include "classes/Messages.hpp"


[[noreturn]]
int main()
{
    using namespace tmockserver;
    using namespace tmockserver::messagelogger;
    using namespace tmockserver::messages;

    Socket server_socket(AddressFamily::IPv4, ConnectionType::TCP);
    server_socket.Bind(8090);
    server_socket.Listen();

    while (true) {
        Socket client_socket = server_socket.Accept();

        auto msgBuffer = std::make_unique<std::byte[]>(BaseMessage::Size());
        client_socket.Read(msgBuffer.get(), BaseMessage::Size());
        const short int msgSize = *reinterpret_cast<short int *>(msgBuffer.get());
        std::byte msgType = *(msgBuffer.get() + sizeof(msgSize));

        switch (static_cast<MessageTypes>(msgType))
        {
            case MessageTypes::CONNECT_REQUEST:
            {
                ConnectRequest(msgSize, msgBuffer, client_socket).Print();
                break;
            }

            default:
                break;
        }

        FatalErrorMessage(TextModes::LITERAL, "Hello tMockServer!").Send(client_socket);

    }
}