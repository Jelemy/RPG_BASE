#pragma once

#include "ECS.h"
#include "game.h"
#include "battleManager.h"
#include "battleGlobal.h"

class action {
private:
    eventType aType;
    Entity* user;
    Entity* recipient;
    string move;

    eventType event;
    partyType actionParty;
    int actionerIndex = 0;
    commands command;
    int commandIndex;
    int recipientIndex;
    



public:
    action (eventType aType, Entity* actioner, commands cmd, int cIndex, Entity* recip);
    action (eventType type);
    eventType getType();
    Entity* getUser();
    Entity* getRecipient();
    string getMove();
    string enact();
};