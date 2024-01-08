#ifndef battleManager_h
#define battleManager_h

#include "game.h"
#include "ECS.h"
#include "components.h"
#include "battleState.h"
#include <vector>
#include <unordered_map>
#include <tuple>

typedef std::vector<Entity*> entities;
typedef tuple<string, int, int, string> artInfo;

class battleState;

class battleManager {
private:
    entities playerParty;
    entities enemyParty;
    Entity* entityTurn;
    std::unordered_map<string, artInfo> artsInfo;
    int playerDecide = 1;
    bool partyTurn;
    int selectTarget = 0;
    int selectItem = 0;
    int selectArt = 0;
    int roundCount = 0;
    void performPhysical(string artName, Entity* recipient);
    void performMagic(string artName, Entity* recipient);
    //void performHeal(string artName, Entity* recipient);
public:
    battleManager(entities &playerP, entities &enemyP);
    Entity* getTurn();
    string checkOutcome();
    void performAttack(int recipientIndex);
    void performArt(int artIndex, int recipientIndex);
    void performHeal(string artName, Entity* recipient);

};

#endif