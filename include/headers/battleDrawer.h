#pragma once

#include "game.h"
#include "ECS.h"
#include "components.h"
#include "battleManager.h"
#include "textManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class battleManager;
class battleState;
typedef std::vector<Entity*> entities;
class battleDrawer {
private:
    entities playerParty;
    entities enemyParty;
    entities uiBoxes;
    Entity* entityTurn;
    bool partyTurn;
    textManager* text;

public:
    battleDrawer(entities &playerP, entities &enemyP);
    void setTurn(Entity* e);
    void drawMenu();
    void drawSubMenu();
    void drawPartyBox();
    void drawMessage();
    void drawBG();
    void drawSelect(int move);
    void drawText(string txt);


};

