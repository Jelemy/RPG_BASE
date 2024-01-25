#ifndef battleGlobal_H
#define battleGlobal_H

#include "ECS.h"
#include <string>
#include <unordered_map>
#include <tuple>
#include "battleManager.h"
#include "battleDrawer.h"

class battleManager;
class battleDrawer;
typedef std::vector<Entity*> entities;
typedef tuple<string, int, int, string> artInfo;


extern std::unordered_map<string, artInfo> artsInfo;

enum menuLayer
{
    ACT, ART, ENEMY
};

extern entities enemyParty;
extern battleManager* bManager;
extern battleDrawer* bDrawer;

#endif