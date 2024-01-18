#ifndef GLOBAL_H
#define GLOBAL_H

#include "ECS.h"
#include <string>

typedef std::vector<Entity*> entities;

extern Manager manager;
extern entities playerParty;
extern entities enemyParty;

#endif