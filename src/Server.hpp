//
// Created by stardustvulpine on 2/10/26.
//

#pragma once

#include <Socket.hpp>
#include <Player.hpp>
#include <TNPPackets.hpp>
#include <vector>

constexpr int SERVER_PROTOCOL_VERSION = 318;
constexpr int DEFAULT_PORT = 7777;
constexpr int DEFAULT_MAX_CLIENTS = 8;

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

        std::vector<terraria::Player> &PlayerList();
        terraria::Player *GetFreePlayer();

        //static void Send(const net::Socket &socket, std::unique_ptr<packets::BasePacket> packet);

        private:
        int m_serverVersion = SERVER_PROTOCOL_VERSION;
        net::Socket m_socket;
        std::vector<terraria::Player> m_player_list;
        std::mutex m_GetFreePlayerMutex;
        Config m_config = Config();

        void Run();
        void ConsoleLoop();
        static bool Disconnect(terraria::Player *player, const std::string& reason);

    };
} // tmockserver