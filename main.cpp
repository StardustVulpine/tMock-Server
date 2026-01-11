#include <iostream>
#include <cerrno>
#include <memory>
#include <cstring>
#include <unistd.h>

#include "Exception.h"
#include "structs/messages.hpp"
#include "./classes/Socket.h"
#include "./classes/Log.h"
#include "classes/InitMessage.hpp"

std::string errorText = "Hello Mock Terraria Server sdasdsadasda";

int main()
{
    using namespace tmockserver;
    using namespace tmockserver::messagelogger;
    using namespace tmockserver::messages;

    Socket server_socket(AdressFamily::IPv4, ConnectionType::TCP);
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

        auto msgBuffer = std::make_unique<char[]>(InitMessage::Size());
        client_socket.Read(msgBuffer.get(), InitMessage::Size());
        std::stringstream ss;
        ss.write(msgBuffer.get(), InitMessage::Size());
        InitMessage i_msg(std::move(ss));
        i_msg.Print();

        // -----------------------

        error_message errorMsg;
        errorMsg.msg_type = 2;
        for (int i = 0; i < errorText.size(); i++) {
            errorMsg.payload_msg[i] = errorText[i];
        }
        errorMsg.payload_size = errorText.size();
        errorMsg.payload_msg[errorText.size()] = '\0';
        errorMsg.msg_size = sizeof(errorMsg.msg_size) + sizeof(errorMsg.msg_type) + sizeof(errorMsg.msg_type2) + sizeof(errorMsg.payload_size) + errorText.size();

        if (write(client_socket, &errorMsg, sizeof(error_message)) == -1) {
            perror(strerror(errno));
        }
        //write(client_socket, "dupa", sizeof("dupa"));


    }



    return 0;
}