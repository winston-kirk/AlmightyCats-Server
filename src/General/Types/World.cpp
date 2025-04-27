#include "General/Types/World.hpp"

namespace Game::Types::World
{
    void to_json(json &j, const Vector2 &v)
    {
        j = json{{"X",v.x},{"Y",v.y}};
    }

    void from_json(const json &j, Vector2 &v)
    {
        j.at('X').get_to(v.x);
        j.at('Y').get_to(v.y);
    }
}
