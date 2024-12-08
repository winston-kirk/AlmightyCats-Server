#pragma once

#include "General/Definitions.hpp"
#include "General/Types/Player.hpp"

namespace Game
{
    using namespace Types;

    class PlayerController
    {
        private:
            Player::Player players[MAX_PLAYERS];

        public:
            PlayerController();
    };
}
