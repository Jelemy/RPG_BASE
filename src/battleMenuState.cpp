#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleMenuState.h>
#include <global.h>




battleMenuState battleMenuState::m_battleMenuState;

// Manager is a class that manages all the entities.




void battleMenuState::init()
{
    printf("menu\n");
    std::cout << playerParty[0]->getComponent<statsComponent>().HP() << std::endl;
    std::cout << playerParty.size() << std::endl;

}

void battleMenuState::clean()
{
	printf("battleMenuState Cleanup\n");
}

void battleMenuState::pause()
{
	printf("battleMenuState Pause\n");
}

void battleMenuState::resume()
{
	printf("battleMenuState Resume\n");
}

void battleMenuState::handleEvents(game* game)
{

}

// split logic into differen handler functions
void battleMenuState::handleSubEvents(battleState* battle)
{
    if (currLayer == ACT) {
        handleAct();
    }
    else if (currLayer == ART) {
        handleArt();
    }
    else if (currLayer == ENEMY) {
        handleEnemy(battle);
    }
    else if (currLayer == ALLY) {
        handleAlly(battle);
    }
}

void battleMenuState::handleAct() {
    optionMax = 1;
    SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
                    case SDLK_w:
                        std::cout << get<1>(artsInfo["Heal"]) << std::endl;
                        if (actionSelect == 0) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = -1;
                            actionSelect -= 1;
                        }
                        break;
                    case SDLK_s:
                        if (actionSelect == optionMax) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = 1;
                            actionSelect += 1;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (actionSelect == 0) {
                            command = BASH;
                            eType = DAMAGE;
                            currLayer = ENEMY;
                        }
                        else if (actionSelect == 1 && currLayer == ACT) {
                            command = ARTS;
                            currLayer = ART;
                            actionSelect = 0;
                            selectMove = 0;
                            
                        }
                        break;
				}
				break;
		}
	}
}

void battleMenuState::handleArt() {

    optionMax = playerParty[actionerIndex]->getComponent<statsComponent>().art().size() - 1;
    SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
                    case SDLK_w:
                        if (actionSelect == 0) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = -1;
                            actionSelect -= 1;
                        }
                        break;
                    case SDLK_s:
                        if (actionSelect == optionMax) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = 1;
                            actionSelect += 1;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (get<0>(artsInfo[playerParty[currPlayer]->getComponent<statsComponent>().art()[actionSelect]]) == "heal") {
                            currLayer = ALLY;
                            eType = HEAL;
                        } else {
                            currLayer = ENEMY;
                            eType = DAMAGE;
                        }
                        commandIndex = actionSelect;
                        actionSelect = 0;
                        selectMove = 0;
                        break;
                    case SDLK_DOWN:
                        currLayer = ACT;
                        actionSelect = 1;
                        selectMove = 0;
                        break;
				}
				break;
		}
	}

}

void battleMenuState::handleEnemy(battleState* battle) {
    optionMax = 1;
    SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
                    case SDLK_a:
                        if (actionSelect == 0) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = -1;
                            actionSelect -= 1;
                        }
                        break;
                    case SDLK_d:
                        if (actionSelect == optionMax) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = 1;
                            actionSelect += 1;
                        }
                        break;
                    case SDLK_RIGHT:
                        recipientIndex = actionSelect;
                        actionList.push_back(std::make_unique<action>(eType, playerParty[actionerIndex], command, commandIndex, enemyParty[recipientIndex]));
                        if (actionList.size() == playerParty.size()) {
                            //battleActionState* nextState = battleActionState::createInstance(std::move(initialActions));
	                        //this->changeBattleState(nextState);
                        } else {
                            currPlayer += 1;
                            actionerIndex += 1;
                            actionSelect = 0;
                            currLayer = ACT;
                            selectMove = 0;
                        }
                        break;
                    case SDLK_DOWN:
                        if (command == BASH) {
                            currLayer = ACT;
                        }
                        else if (command == ARTS) {
                            currLayer = ART;
                        }
                        actionSelect = 0;
                        selectMove = 0;
                        break;
				}
				break;
		}
	}
}

void battleMenuState::handleAlly(battleState* battle) {
    optionMax = 1;
    SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
                    case SDLK_a:
                        if (actionSelect == 0) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = -1;
                            actionSelect -= 1;
                        }
                        break;
                    case SDLK_d:
                        if (actionSelect == optionMax) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = 1;
                            actionSelect += 1;
                        }
                        break;
                    case SDLK_RIGHT:
                        recipientIndex = actionSelect;
                        break;
                    case SDLK_DOWN:
                        currLayer = ART;
                        actionSelect = 0;
                        selectMove = 0;
                        break;
				}
				break;
		}
	}
}

void battleMenuState::update(game* game) 
{

}

void battleMenuState::draw(game* game) 
{
    bDrawer->drawMenu(actionerIndex);
    if (currLayer == ART) {
        bDrawer->drawSubMenu(currPlayer);
    }
    bDrawer->drawSelect(selectMove, actionSelect, currLayer);
    bDrawer->drawPartyBox();
    selectMove = 0;

}