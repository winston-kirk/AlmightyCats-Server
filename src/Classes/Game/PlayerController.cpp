#include "Classes/Game/PlayerController.hpp"

using namespace Game;

PlayerController::PlayerController(){}

void PlayerController::handleAction(std::string actionString)
{
    json actionJSON = this->parseAction(actionString);

    this->executeAction(actionJSON);
}

json PlayerController::parseAction(std::string actionString)
{
    //std::cout << "ActionString: " << actionString << std::endl;

    json actionMessage = json::parse(actionString);

    return actionMessage;
}

void PlayerController::executeAction(json actionJSON)
{
    Player::PlayerAction playerAction = actionJSON.at("player_action").at("flag");

    if(playerAction == (Player::PlayerAction) Player::PlayerActions::ACTION_CONNECT_HANDSHAKE_CLIENT)
    {
        this->broadcast(actionJSON, {});
        return;
    }

    if(playerAction == (Player::PlayerAction) Player::PlayerActions::ACTION_MOVE_TO)
    {
        Player::PlayerID fromPlayerID = actionJSON.at("payload").at("player_id");

        for(Player::Player &p : this->players)
        {
            if(p.playerID == fromPlayerID)
            {
                p.position.x = actionJSON.at("payload").at("position").at("X");
                p.position.y = actionJSON.at("payload").at("position").at("Y");
            }
        }

        this->broadcast(actionJSON, {fromPlayerID});
    }
    else
    {
        Player::PlayerID fromPlayerID = actionJSON.at("payload").at("player_id");
        this->broadcast(actionJSON, {fromPlayerID});
    }
}

Player::PlayerID PlayerController::getPlayerID()
{
    return this->playerCount++;
}

void PlayerController::addPlayer(Player::PlayerID newPlayerID, std::shared_ptr<websocket::stream<tcp::socket>> webSocket)
{
    Player::Player p
    (
        newPlayerID,
        webSocket
    );

    this->players.push_back(p);
}

void PlayerController::broadcast(json actionJSON, std::vector<Player::PlayerID> excludePlayerIDs = {})
{
    for(Player::Player &p : this->players)
    {
        bool exclude = false;
        for(Player::PlayerID pID : excludePlayerIDs)
        {
            if(pID == p.playerID)
            {
                exclude = true;
            }
        }

        if(!exclude)
        {
            p.webSocket->write(net::buffer(actionJSON.dump()));
        }
    }
}

void PlayerController::sendPlayerList(Player::PlayerID playerID)
{
    json playerList{};

    std::shared_ptr<websocket::stream<tcp::socket>> webSocket;
    bool found = false;
    for(Player::Player &p : this->players)
    {
        if(p.playerID == playerID)
        {
            webSocket = p.webSocket;
            found = true;
        }

        playerList.push_back(p);
    }

    if(found)
    {
        json playerListMessage
        {
            {
                "player_action",
                {
                    { "flag", Player::PlayerActions::ACTION_LIST_PLAYERS }
                }
            },
            {
                "payload",
                {
                    { "player_list", playerList }
                }
            }
        };

        webSocket->write(net::buffer(playerListMessage.dump()));
    }
}
