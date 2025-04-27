#include "General/Types/Player.hpp"

namespace Game::Types::Player
{
    void from_json(const json &j, Player &player){}

    void to_json(json &j, const Player &player)
    {
        j = json
        {
            { "player_id", player.playerID },
            { "position", player.position }
        };
    }
}
