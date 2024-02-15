#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleActionState.h>
#include <battleMenuState.h>
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

void battleActionState::handleSubEvents(battleState* battle)
{

	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
                        printf("HI");
                        if (currAction < actionList.size() - 1) {
                            currAction++;
							currLine = actionList[currAction]->enact();
                        }
						else if  (currAction == actionList.size() - 1) {
							for (auto it = enemyParty.begin(); it != enemyParty.end();) {
								if ((*it)->getComponent<statsComponent>().HP() <= 0) {
									it = enemyParty.erase(it);
								} else {
									++it;
								}
							}
							printf("enemy size");
							std::cout << enemyParty.size() << std::endl;
							battle->changeBattleState(battleMenuState::instance());
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