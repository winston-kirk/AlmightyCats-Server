#pragma once

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <nlohmann/json.hpp>

#include "Classes/Game/GameController.hpp"
#include "Classes/Game/PlayerController.hpp"
#include "General/Types/Player.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;

using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

namespace Game
{
    class Server
    {

        private:
            //GameController gameController = GameController();
            PlayerController playerController = PlayerController();
            std::string bindAddress;
            int port;

        public:
            Server();
            Server(std::string _bindAddress, int _port);
            int startup();
            void sessionHandler(tcp::socket socket, ssl::context &ctx);
    };
}
