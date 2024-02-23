#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleActionState.h>
#include <battleMenuState.h>
#include <titleState.h>
#include <battleGlobal.h>

// Manager is a class that manages all the entities.

battleActionState::battleActionState (actions a) : actionList(std::move(a)){
}

void battleActionState::init()
{
	printf("hello\n");
    //std::cout << actionList[0]->enact() << std::endl;
	currLine = actionList[0]->enact();
	std::cout << currLine << std::endl;
}

void battleActionState::clean()
{
	printf("battleActionState Cleanup\n");
}

void battleActionState::pause()
{
	printf("battleActionState Pause\n");
}

void battleActionState::resume()
{
	printf("battleActionState Resume\n");
}

void battleActionState::handleEvents(game* game)
{
}

bool battleActionState::checkEnemiesDead() {
    for (Entity* member : enemyParty) {
        if (member->getComponent<statsComponent>().HP() > 0) {
            return false; // At least one party member is alive
        }
    }
    return true; // All party members are dead
}

bool battleActionState::checkPartyDead() {
    for (Entity* member : playerParty) {
        if (member->getComponent<statsComponent>().HP() > 0) {
            return false; // At least one party member is alive
        }
    }
    return true; // All party members are dead
}

void battleActionState::updateActionState() {
	for (auto it = enemyParty.begin(); it != enemyParty.end();) {
		if ((*it)->getComponent<statsComponent>().HP() <= 0) {
			it = enemyParty.erase(it);
		} else {
			++it;
		}
	}
	
	if (checkEnemiesDead()) {
		actionList.clear();
		actionList.push_back(std::make_unique<action>(VICTORY));
		currAction = -1;
		battleCondition = WON;
	} else if (checkPartyDead()) {
		actionList.clear();
		actionList.push_back(std::make_unique<action>(DEFEAT));
		currAction = -1;
		battleCondition = LOST;
	}
}
void battleActionState::handleSubEvents(battleState* battle, game* game)
{

	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
                        printf("HI");
						std::cout << actionList.size()<< std::endl;
						std::cout << currAction << std::endl;
						std::cout << (currAction <= actionList.size()) << std::endl;
						if (currAction == -1) {
							currAction++;
							currLine = actionList[currAction]->enact();
						}
                        else if (currAction < (actionList.size() - 1)) {
							printf("in");
                            currAction++;
							currLine = actionList[currAction]->enact();
							if (battleCondition == CONTINUE) {
								updateActionState();
							}
                        }
						else if  (currAction == actionList.size() - 1) {
							if  (battleCondition == WON || battleCondition == LOST) {
								game->changeState( titleState::instance() );
							} else if (battleCondition == CONTINUE) {
								printf("enemy size");
								std::cout << enemyParty.size() << std::endl;
								battle->changeBattleState(battleMenuState::instance());
							}
						}
                        break;	
				}
				break;
		}
	}
}

void battleActionState::update(game* game) 
{
	
}

void battleActionState::draw(game* game) 
{
    bDrawer->drawMessage();
    bDrawer->drawText(currLine);
}