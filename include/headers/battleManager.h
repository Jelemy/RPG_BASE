#ifndef battleManager_h
#define battleManager_h

#include "game.h"
#include "ECS.h"
#include "components.h"
#include "battleState.h"
#include "battleGlobal.h"
#include "global.h"
#include <vector>
#include <unordered_map>
#include <tuple>

class battleState;

class battleManager {

public:
    battleManager();
    int performPhysical(Entity* actioner, string art, Entity* recipient);
    int performMagic(Entity* actioner, string art, Entity* recipient);
    string checkOutcome();
    int performAttack(Entity* actioner, Entity* recipient);
    int performArt(Entity* actioner, Entity* recipient, int artIndex);
    int performHeal(Entity* actioner, string art, Entity* recipient);

};

#endif