#pragma once

namespace Game::Types::Player
{
    typedef int PlayerAction;

    enum class PlayerActions : PlayerAction
    {
        ACTION_NONE = 0,
        ACTION_CONNECT_HANDSHAKE_CLIENT = 1,
        ACTION_CONNECT_HANDSHAKE_SERVER = 2,
        ACTION_LOGIN = 4,
        ACTION_LOGOUT = 8,
        ACTION_SPAWN = 16,
        ACTION_LIST_PLAYERS = 32,
        ACTION_MOVE_TO = 64,
        ACTION_INVALID = 512
    };

}
