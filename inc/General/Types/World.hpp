#pragma once

namespace Game::Types::World
{
    struct Position
    {
        int x;
        int y;
    };

    enum Items
    {
        ITEM_NONE = 0,
        ITEM_DIRT = 100,
        ITEM_GRASS = 200,
        ITEM_WATER = 300
    };
}
