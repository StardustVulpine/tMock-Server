//
// Created by stardustvulpine on 2/10/26.
//

#pragma once

#include <Socket.hpp>
#include <Player.hpp>
#include <vector>

#define RESET_COLOR "\033[0m"
#define GREEN "\033[38;2;0;255;1m"
#define YELLOW "\033[38;2;255;191;0m"
#define RED "\033[38;2;220;20;60m"

constexpr int SERVER_PROTOCOL_VERSION = 318;
constexpr int DEFAULT_PORT = 7777;
constexpr int DEFAULT_MAX_CLIENTS = 8;

using namespace tmockserver::networking;
using namespace tmockserver::gamestate;

namespace tmockserver
{
    class Server
    {
        struct Config
        {
            int port = DEFAULT_PORT;
            int max_players = DEFAULT_MAX_CLIENTS;
            std::optional<std::string> password = std::nullopt;
        };

        public:
        explicit Server();
        ~Server() = default;

        void Start();

        std::vector<Player> &PlayerList();
        Player *GetFreePlayer();

        private:
        int m_serverVersion = SERVER_PROTOCOL_VERSION;
        Socket m_socket;
        std::vector<Player> m_player_list;
        Config m_config = Config();

        void Run();

    };
} // tmockserver