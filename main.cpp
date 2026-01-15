#include <iostream>
#include <cerrno>
#include <memory>
#include <cstring>
#include <unistd.h>

#include "Exception.hpp"
#include "TextModes.h"
#include "structs/messages.hpp"
#include "./classes/Socket.hpp"
#include "./classes/Log.hpp"
#include "classes/messages/ConnectRequest.hpp"
#include "enums/MessageTypes.h"


std::string errorText = "CLI.DeleteConfirmation";

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

        // -----------------------

        error_message errorMsg;
        errorMsg.msg_type = 2;
        errorMsg.network_text_mode = static_cast<unsigned char>(TextModes::LOCALIZATION_KEY);
        for (int i = 0; i < errorText.size(); i++) {
            errorMsg.payload_msg[i] = errorText[i];
        }
        errorMsg.payload_size = errorText.size();
        errorMsg.payload_msg[errorText.size()] = '\0';
        errorMsg.msg_size = sizeof(errorMsg.msg_size) + sizeof(errorMsg.msg_type) + sizeof(errorMsg.network_text_mode) + sizeof(errorMsg.payload_size) + errorText.size();

        if (write(client_socket, &errorMsg, sizeof(error_message)) == -1) {
            perror(strerror(errno));
        }

        // ----------------------
    }
}