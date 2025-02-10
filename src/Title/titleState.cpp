
#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <titleState.h>
#include <overWorldstate.h>

titleState titleState::m_titleState;

void titleState::init()
{
    SDL_Surface* tempSurface = IMG_Load("assets/Title.png");
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
}

void titleState::clean()
{
	//printf("titleState Cleanup\n");
}

void titleState::pause()
{
	//printf("titleState Pause\n");
}

void titleState::resume()
{
	//printf("titleState Resume\n");
}

void titleState::handleEvents(game* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_RETURN:
						game->changeState( overWorldState::instance() );
						break;
						
					case SDLK_ESCAPE:
						game->quit();
						break;
				}
				break;
		}
	}
}

void titleState::update(game* game) 
{
}

void titleState::draw(game* game) 
{

}