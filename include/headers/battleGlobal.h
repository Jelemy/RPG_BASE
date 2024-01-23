#ifndef battleGlobal_H
#define battleGlobal_H

#include "ECS.h"
#include <string>
#include "battleManager.h"
#include "battleDrawer.h"

class battleManager;
class battleDrawer;
typedef std::vector<Entity*> entities;

enum menuLayer
{
    ACT, ART
};

extern entities enemyParty;
extern battleManager* bManager;
extern battleDrawer* bDrawer;

#endif