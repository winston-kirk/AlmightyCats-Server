#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include "General/Definitions.hpp"
#include "General/Types/World.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;

using tcp = boost::asio::ip::tcp;

namespace Game::Types::Player
{
    typedef int PlayerSlot;
    typedef int PlayerCount;
    typedef int PlayerID;

    struct Player
    {
        public:
            PlayerSlot playerSlot;
            PlayerID playerID;
            char playerName[MAX_PLAYER_NAME];
            World::Vector2 position;
            World::Items inventorySlots[MAX_INVENTORY_SLOTS];
            std::shared_ptr<websocket::stream<tcp::socket>> webSocket;

            Player()
            {
                this->position.x = 0;
                this->position.y = 0;
            }

            Player(PlayerID playerID, std::shared_ptr<websocket::stream<tcp::socket>> webSocket)
            {
                this->position.x = 0;
                this->position.y = 0;
                this->playerID = playerID;
                this->webSocket = webSocket;
            }
    };

    void from_json(const json &j, Player &player);
    void to_json(json &j, const Player &player);
}
