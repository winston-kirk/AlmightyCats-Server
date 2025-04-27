#include "Classes/Game/Server.hpp"

using namespace Game;

Server::Server() : bindAddress(DEFAULT_BIND_ADDRESS), port(DEFAULT_PORT) {}

Server::Server(std::string _bindAddress, int _port) : bindAddress(_bindAddress), port(_port){}

void Server::sessionHandler(tcp::socket socket, ssl::context &ctx)
{
    try
    {
        std::shared_ptr<websocket::stream<tcp::socket>> ws(new websocket::stream<tcp::socket>{std::move(socket)});

        ws->set_option(websocket::stream_base::decorator
        (
            [](websocket::response_type &res)
            {
                res.set
                (
                    http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) + " websocket-server-sync"
                );
            }
        ));

        ws->accept();
        ws->text(true);

        Player::PlayerID newPlayerID = this->playerController.getPlayerID();
        this->playerController.addPlayer(newPlayerID, ws);

        json actionConnectHandshake =
        {
            {
                "player_action",
                {
                    { "flag", Player::PlayerActions::ACTION_CONNECT_HANDSHAKE_SERVER }
                }
            },
            {
                "payload" ,
                {
                    { "handshake", "ClanCats - Purr Purr!" },
                    { "player_id", newPlayerID}
                }
            }
        };

        json actionSpawn =
        {
            {
                "player_action",
                {
                    { "flag", Player::PlayerActions::ACTION_SPAWN }
                }
            },
            {
                "payload" ,
                {
                    { "player_id", newPlayerID },
                    { "position", World::Vector2(0,0) },
                    { "rotation", World::Vector2(0,0) }
                }
            }
        };

        ws->write(net::buffer(actionConnectHandshake.dump()));
        //ws->write(net::buffer(actionSpawn.dump()));

        this->playerController.broadcast(actionSpawn, {});
        this->playerController.sendPlayerList(newPlayerID);

        for(;;)
        {
            beast::flat_buffer buffer;

            ws->read(buffer);

            if(ws->got_text())
            {
                this->playerController.handleAction(beast::buffers_to_string(buffer.data()));
            }
        }
    }
    catch(beast::system_error const &se)
    {
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch(std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int Server::startup()
{
    try
    {
        auto const address = net::ip::make_address(this->bindAddress);
        auto const port = static_cast<unsigned short>(this->port);

        net::io_context ioc(1);

        ssl::context ctx(ssl::context::tlsv12);

        //load_server_certificate(ctx);

        tcp::acceptor acceptor(ioc, {address, port});
        for(;;)
        {
            tcp::socket socket(ioc);

            acceptor.accept(socket);

            std::cout <<  "Acceptor accepted..." << std::endl;

            std::thread
            (
                &Server::sessionHandler,
                this,
                std::move(socket),
                std::ref(ctx)
            ).detach();
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
