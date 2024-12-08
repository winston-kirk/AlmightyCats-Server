#pragma once

#include "General/Definitions.hpp"
#include "General/Types/World.hpp"

namespace Game::Types::Player
{
    typedef int PlayerID;

    struct Player
    {
        public:
            PlayerID id;
            char playerName[MAX_PLAYER_NAME];
            World::Position position;
            World::Items inventorySlots[MAX_INVENTORY_SLOTS];
    };
}
