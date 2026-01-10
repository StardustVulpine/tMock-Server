#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "messages.h"


std::string errorText = "Hello Mock Terraria Server sdasdsadasda";

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8090);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);


    bind(server_socket, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr));


    if (listen(server_socket, SOMAXCONN) == -1) {
        perror(strerror(errno));
        return 1;
    }

    sockaddr_in client_addr {};
    int client_len = sizeof(client_addr);

    while (true) {
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr*>(&client_addr), reinterpret_cast<socklen_t*>(&client_len));

        if (client_socket == -1) {
            perror(strerror(errno));
            continue;
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