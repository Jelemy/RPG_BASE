#ifndef battleGlobal_H
#define battleGlobal_H

#include "ECS.h"
#include <string>
#include "battleManager.h"
#include "battleDrawer.h"

typedef std::vector<Entity*> entities;

extern entities enemyParty;
extern battleManager* bManager;
extern battleDrawer* bDrawer;

#endif