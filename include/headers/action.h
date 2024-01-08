#pragma once

#include "ECS.h"
#include "game.h"
#include "battleManager.h"

enum actionType
{
    BATTLESTART, VICTORY, DEFEAT, DAMAGE, HEAL, ACTION
};

class action {
private:
    actionType aType;
    Entity* user;
    Entity* recipient;
    string move;

public:
    static battleManager* bm;
    action (actionType type, Entity* usr, Entity* recip, string mv);
    action (actionType type);
    actionType getType();
    Entity* getUser();
    Entity* getRecipient();
    string getMove();
    string enact();
};