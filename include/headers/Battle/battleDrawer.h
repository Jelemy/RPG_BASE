#pragma once

#include "game.h"
#include "ECS.h"
#include "components.h"
#include "battleManager.h"
#include "textManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "battleGlobal.h"

class battleManager;
class battleState;
typedef std::vector<Entity*> entities;
class battleDrawer {
private:
    entities uiBoxes;
    Entity* entityTurn;
    bool partyTurn;
    textManager* text;

public:
    battleDrawer();
    void setTurn(Entity* e);
    void drawMenu(int currPlayer);
    void drawSubMenu(int currPlayer);
    void drawPartyBox();
    void drawMessage();
    void drawBG();
    void drawSelect(int move, int action, menuLayer menu);
    void drawText(string txt);
    void drawEnemy();


};

