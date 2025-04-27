#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <vector>

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <nlohmann/json.hpp>

#include "General/Definitions.hpp"
#include "General/Types/Player.hpp"
#include "General/Types/PlayerAction.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;

using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

namespace Game
{
    using namespace Types;

    class PlayerController
    {
        private:
            std::vector<Player::Player> players;
            Player::PlayerCount playerCount = 0;

            Player::PlayerSlot assignSlot();
            json parseAction(std::string actionString);
            void executeAction(json actionJSON);

        public:
            PlayerController();
            void addPlayer(Player::PlayerID newPlayerID, std::shared_ptr<websocket::stream<tcp::socket>> webSocket);
            void handleAction(std::string actionString);
            void broadcast(json actionJSON, std::vector<Player::PlayerID> excludePlayerIDs);
            void sendPlayerList(Player::PlayerID playerID);
            Player::PlayerID getPlayerID();
    };
}
