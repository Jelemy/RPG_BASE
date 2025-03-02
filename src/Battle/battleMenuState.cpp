#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleMenuState.h>
#include <global.h>
#include <enemyAI.h>

battleMenuState battleMenuState::m_battleMenuState;
enemyAI* eAI;

void battleMenuState::init()
{
    currLayer = ACT;
    currPlayer = findNextAlive(0);
    selectMove = 0;
    actionSelect = 0;
    actionList.clear();
    eAI = new enemyAI();

}

int battleMenuState::findNextAlive(int index) {
    int partySize = playerParty.size();
    int currentIndex = index % partySize;  // Normalize the start index

    // Iterate through the player party to find the next alive member
    int iterations = 0;  // Track the number of iterations
    while (iterations < partySize) {
        if (playerParty[currentIndex]->getComponent<statsComponent>().HP() > 0) {
            // Found an alive member, return its index
            return currentIndex;
        }
        currentIndex = (currentIndex + 1) % partySize;  // Move to the next index
        iterations++;  // Increment the iteration count
    }

    // If looped through the entire party once, return -1 to indicate no alive member found
    return -1;  // Or any other suitable indicator for no alive member found
}

int battleMenuState::getNumAlive() {
    int numAlive = 0;
    for (Entity* player: playerParty) {
        if (player->getComponent<statsComponent>().HP() > 0) {
            numAlive++;
        }                    
    }
    return numAlive;
}
void battleMenuState::clean()
{
	//printf("battleMenuState Cleanup\n");
}

void battleMenuState::pause()
{
	//printf("battleMenuState Pause\n");
}

void battleMenuState::resume()
{
	//printf("battleMenuState Resume\n");
}

void battleMenuState::handleEvents(game* game)
{

}

// split menu layers into differen handler functions
void battleMenuState::handleSubEvents(battleState* battle, game* game)
{
    // Handle initial actions layer
    if (currLayer == ACT) {
        handleAct();
    }
    // Handle art selection
    else if (currLayer == ART) {
        handleArt();
    }
    // Handle enemy target selection
    else if (currLayer == ENEMY) {
        handleEnemy(battle);
    }
    // Handle ally target selection (for healing and buffs)
    else if (currLayer == ALLY) {
        handleAlly(battle);
    }
}

void battleMenuState::handleAct() {
    // define current max actions, should be put into a variable else where
    optionMax = 1;
    SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
                    // case press up
                    case SDLK_w:
                        if (actionSelect == 0) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = -1;
                            actionSelect -= 1;
                        }
                        break;
                    // case press down
                    case SDLK_s:
                        if (actionSelect == optionMax) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = 1;
                            actionSelect += 1;
                        }
                        break;
                    // case press right arrow key
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

    optionMax = playerParty[currPlayer]->getComponent<statsComponent>().art().size() - 1;
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
    optionMax = enemyParty.size() - 1;
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
                        // once enemy selected, action is appended to action list
                        actionList.push_back(std::make_unique<action>(eType, playerParty[currPlayer], command, commandIndex, enemyParty[recipientIndex]));
                        // When all actions is retrieved generate enemy actions and append to action list before changing
                        // battle action state.
                        if (actionList.size() == getNumAlive()) {
                            for (Entity* enemy: enemyParty) {
                                actionList.push_back(eAI->generateAction(enemy));
                            }
                            battleActionState* nextState = battleActionState::createInstance(std::move(actionList));
	                        battle->changeBattleState(nextState);
                        } else {
                            currPlayer = findNextAlive(currPlayer + 1);
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
                        actionList.push_back(std::make_unique<action>(eType, playerParty[currPlayer], command, commandIndex, playerParty[recipientIndex]));
                        if (actionList.size() == getNumAlive()) {
                            for (Entity* enemy: enemyParty) {
                                actionList.push_back(eAI->generateAction(enemy));
                                
                            }
                            battleActionState* nextState = battleActionState::createInstance(std::move(actionList));
	                        battle->changeBattleState(nextState);
                        } else {
                            currPlayer = findNextAlive(currPlayer + 1);
                            actionSelect = 0;
                            currLayer = ACT;
                            selectMove = 0;
                        }
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
    // current player passed in so we know which actions and arts to display
    bDrawer->drawMenu(currPlayer);
    if (currLayer == ART) {
        bDrawer->drawSubMenu(currPlayer);
    }
    // selectMove is the direction the arrow moves in
    // actionSelect is the current index of the current array of options
    bDrawer->drawSelect(selectMove, actionSelect, currLayer);
    bDrawer->drawPartyBox();
    selectMove = 0;

}