#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Game::Types::World
{
    struct Vector2
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

    void to_json(json &j, const Vector2 &v);
    void from_json(const json &j, Vector2 &v);
}
