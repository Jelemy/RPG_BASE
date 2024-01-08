#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleActionState.h>
#include <battleMenuState.h>



battleActionState battleActionState::m_battleActionState;

// Manager is a class that manages all the entities.


battleDrawer* battleMenuState::bDrawer = nullptr;

void battleActionState::init()
{
	battleMenuState::bDrawer = battleActionState::bDrawer;
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
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						game->changeState( battleMenuState::instance() );
						//currAction = 1;
						break;

					case SDLK_ESCAPE:
						game->quit();
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
    SDL_RenderClear(game::renderer);
    if (bDrawer == nullptr) {
        std::cout << "hello" << std::endl;
    }
    //std::cout << "hello" << std::endl;
    bDrawer->drawBG();
    bDrawer->drawMessage();
    bDrawer->drawText(actionList[currAction]->enact());
	//currAction = 1;
    SDL_RenderPresent(game::renderer);

}