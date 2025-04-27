#include <iostream>

#include "Classes/Game/Server.hpp"

int main(int argc, char **argv)
{
    Game::Server server = Game::Server();

    std::cout << "Starting server..." << std::endl;

    server.startup();

    return 0;
}
