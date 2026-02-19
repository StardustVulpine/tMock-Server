#include "Server.hpp"

int main()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif



    tmockserver::Server server;
    server.Start();

    return 0;
}