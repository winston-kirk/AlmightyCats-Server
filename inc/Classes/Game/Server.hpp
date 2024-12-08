#pragma once

#include <boost/beast.hpp>

#include "Classes/Game/GameController.hpp"
#include "Classes/Game/PlayerController.hpp"

namespace Game
{
    class Server
    {
        private:
            GameController gameController();
            PlayerController playerController();

        public:
            Server();
    };
}
