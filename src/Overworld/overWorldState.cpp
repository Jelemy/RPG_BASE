#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <overWorldState.h>
#include <battleActionState.h>
#include <battleState.h>
#include <battleMenuState.h>
#include <action.h>
#include <ECS.h>
#include <components.h>
#include <global.h>
#include <Vector2D.h>

overWorldState overWorldState::m_overWorldState;

// Manager is a class that manages all the entities.
Manager manager;
auto& player(manager.addEntity());

void overWorldState::init()
{
/*
    SDL_Surface* tempSurface = IMG_Load("assets/OverworldPlaceHolder.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_Rect srcRect, destRect;
    srcRect.w = 640;
    srcRect.h = 480;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = 640;
    destRect.h = 480;
    destRect.x = 0;
    destRect.y = 0;
    SDL_RenderClear(game::renderer);
    SDL_RenderCopy(game::renderer, tex, &srcRect, &destRect);
    SDL_RenderPresent(game::renderer);
*/
	player.addComponent<transformComponent>();
	player.addComponent<spriteComponent>("assets/dawnsheet2.png");
}

void overWorldState::clean()
{
	printf("overWorldState Cleanup\n");
}

void overWorldState::pause()
{
	printf("overWorldState Pause\n");
}

void overWorldState::resume()
{
	printf("overWorldState Resume\n");
}

void overWorldState::handleEvents(game* game)
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
					{
						game->changeState( battleState::instance() );
						break;
					}
					case SDLK_ESCAPE:
						game->quit();
						break;
				}
				break;
		}
	}
}

void overWorldState::update(game* game) 
{
	manager.refresh();
	manager.update();
	player.getComponent<transformComponent>().position.Add(Vector2D(5, 0));

}

void overWorldState::draw(game* game) 
{
    SDL_Surface* tempSurface = IMG_Load("assets/OverworldPlaceHolder.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_Rect srcRect, destRect;
    srcRect.w = 640;
    srcRect.h = 480;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = 640;
    destRect.h = 480;
    destRect.x = 0;
    destRect.y = 0;
    SDL_RenderClear(game::renderer);
    SDL_RenderCopy(game::renderer, tex, &srcRect, &destRect);
	manager.draw();
    SDL_RenderPresent(game::renderer);
}