#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleMenuState.h>
#include <battleGlobal.h>




battleMenuState battleMenuState::m_battleMenuState;

// Manager is a class that manages all the entities.




void battleMenuState::init()
{
    printf("menu\n");

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
                        std::cout << actionSelect << std::endl;
                        std::cout << selectMove << std::endl;
                        if (actionSelect == 1) {
                            selectMove = -1;
                            actionSelect = 0;
                            break;
                        }
                        else {
                            selectMove = 0;
                        }
                        break;
                    case SDLK_s:
                        std::cout << actionSelect << std::endl;
                        std::cout << selectMove << std::endl;
                        if (actionSelect == 0) {
                            //std::cout << "hello" << std::endl;
                            selectMove = 1;
                            actionSelect = 1;
                            break;
                        }
                        else {
                            selectMove = 0;
                        }
                 
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
    bDrawer->drawSelect(selectMove);
    selectMove = 0;

}