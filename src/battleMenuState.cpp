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

void battleMenuState::handleSubEvents(battleState* battle)
{
    SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						//game->changeState( battleState::instance() );
						break;
                    case SDLK_w:
                        if (actionSelect == 0) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = -1;
                            actionSelect -= 1;
                        }
                        std::cout << actionSelect << std::endl;
                        std::cout << selectMove << std::endl;
                        std::cout << playerParty[currPlayer]->getComponent<statsComponent>().art()[actionSelect] << std::endl;
                        break;
                    case SDLK_s:
                        if (actionSelect == optionMax) {
                            selectMove = 0;
                        }
                        else {
                            selectMove = 1;
                            actionSelect += 1;
                        }
                        std::cout << actionSelect << std::endl;
                        std::cout << selectMove << std::endl;
                        std::cout << playerParty[currPlayer]->getComponent<statsComponent>().art()[actionSelect] << std::endl;
                        break;
                    case SDLK_RIGHT:
                        if (actionSelect == 0) {
                            
                        }
                        else if (actionSelect == 1) {
                            arts = true;
                            currLayer = ART;
                            actionSelect = 0;
                            selectMove = 0;
                            optionMax = 2;
                        }
                 
                        break;
                    case SDLK_DOWN:
                        arts = false;
                        currLayer = ACT;
                        actionSelect = 1;
                        selectMove = 0;
                        optionMax = 1;
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
    bDrawer->drawMenu();
    if (arts) {
        bDrawer->drawSubMenu(currPlayer);
    }
    bDrawer->drawSelect(selectMove, actionSelect, currLayer);
    bDrawer->drawPartyBox();
    selectMove = 0;

}