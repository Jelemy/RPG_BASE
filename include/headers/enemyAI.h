#pragma once

#include "action.h"
#include "global.h"
#include "battleGlobal.h"
#include <random>

class enemyAI {
private:
    std::unique_ptr<action> aggressiveAction(Entity* enemy);
    std::unique_ptr<action> normalAction(Entity* enemy);
    std::unique_ptr<action> defensiveAction(Entity* enemy);

public:
    std::unique_ptr<action> generateAction(Entity* enemy);
};