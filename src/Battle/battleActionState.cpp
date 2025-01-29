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
	currLine = actionList[0]->enact();
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

// Function updates state of the battle. Removes dead enemies and checks..
// if battle has been won
void battleActionState::updateActionState() {
	// Loop through enemy list and remove if HP is 0.
	for (auto it = enemyParty.begin(); it != enemyParty.end();) {
		if ((*it)->getComponent<statsComponent>().HP() <= 0) {
			it = enemyParty.erase(it);
		} else {
			++it;
		}
	}
	// Check if all enemies are dead.
	// If all dead battle is won
	if (checkEnemiesDead()) {
		actionList.clear();
		actionList.push_back(std::make_unique<action>(VICTORY));
		currAction = -1;
		battleCondition = WON;
	// Check if all player party is dead
	// If all dead battle is lost
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
					// Right arrow key button to progress battle dialogue
					case SDLK_RIGHT:
						// condition is fulfilled only if battle has been lost or won
						// ensures that nothing else is done besides getting the win or lose dialogue
						if (currAction == -1) {
							currAction++;
							currLine = actionList[currAction]->enact();
						}
						// If there are still actions to process, increment through actions list and enact..
						// the action. 
						// Note: enact executes the action and retruns the battle dialogue to convey the action.
                        else if (currAction < (actionList.size() - 1)) {
                            currAction++;
							currLine = actionList[currAction]->enact();
							if (battleCondition == CONTINUE) {
								updateActionState();
							}
                        }
						// If at the end of action list, check of battle has been won, lost or ongoing
						// Quit game if battle is over, or go to menu state if battle is still ongoing
						else if  (currAction == actionList.size() - 1) {
							if  (battleCondition == WON || battleCondition == LOST) {
								game->changeState( titleState::instance() );
							} else if (battleCondition == CONTINUE) {
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