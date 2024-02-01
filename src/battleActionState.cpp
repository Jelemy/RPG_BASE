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
							printf("lol");
                            currAction++;
							std::cout << currAction << std::endl;
							std::cout << actionList.size() << std::endl;
							currLine = actionList[currAction]->enact();
							printf("lol");
							std::cout << currAction << std::endl;
							std::cout << actionList.size() << std::endl;
                        }
						else if  (currAction == actionList.size() - 1) {
							printf("menu");
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