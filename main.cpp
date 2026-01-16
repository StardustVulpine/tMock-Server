#include <iostream>
#include <memory>

#include "Exception.hpp"
#include "TextModes.h"
#include "classes/Socket.hpp"
#include "classes/Log.hpp"
#include "classes/Messages.hpp"


int main()
{
    using namespace tmockserver;
    using namespace tmockserver::messagelogger;
    using namespace tmockserver::messages;

    Socket server_socket(AddressFamily::IPv4, ConnectionType::TCP);
    server_socket.Bind(8090);

    try {
        server_socket.Listen();
    } catch (const Exception& e) {
        std::cerr << e.what() << std::endl;
    }

    while (true) {
        Socket client_socket;

        try {
            auto client_socket_tmp = server_socket.Accept();
            client_socket = client_socket_tmp;
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }

        auto msgBuffer = std::make_unique<char[]>(ConnectRequest::Size());
        client_socket.Read(msgBuffer.get(), ConnectRequest::Size());
        std::stringstream ss;
        ss.write(msgBuffer.get(), ConnectRequest::Size());
        ConnectRequest i_msg(std::move(ss));
        i_msg.Print();

        FatalErrorMessage errorMessage(TextModes::LITERAL, "Hello tMockServer!");

        try {
            auto [fst, snd] = errorMessage.GetContent();
            client_socket.Write(fst.get(), snd);
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }


    }
}