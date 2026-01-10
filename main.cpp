#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "Exception.h"
#include "structs/messages.h"
#include "./classes/Socket.h"


std::string errorText = "Hello Mock Terraria Server sdasdsadasda";

int main()
{
    using namespace tmockserver;

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
            Socket client_socket_tmp (server_socket.Accept());
            client_socket = client_socket_tmp;
        } catch (const Exception& e) {
            std::cerr << e.what() << std::endl;
        }

        init_message message;
        read(client_socket, &message, sizeof(message));
        int msg_size = static_cast<int>(message.payload_size);

        char *t_msg = reinterpret_cast<char*>(malloc(msg_size*sizeof(char)));

        read(client_socket, t_msg, msg_size);

        printf("Message Size: %i \n", message.msg_size);
        printf("Message Type: %i \n", sizeof(error_message));
        printf("Message: %s \n", t_msg);
        free(t_msg);


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