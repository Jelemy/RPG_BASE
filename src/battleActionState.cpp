#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <battleActionState.h>
#include <battleMenuState.h>

// Manager is a class that manages all the entities.


battleDrawer* battleMenuState::bDrawer = nullptr;

battleActionState::battleActionState (actions a) : actionList(std::move(a)){
}

void battleActionState::init()
{

	SDL_Surface* tempSurface = IMG_Load("assets/start.jpg");
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
	printf("hello\n");
    std::cout << actionList[0]->enact() << std::endl;
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
	
}

void battleActionState::update(game* game) 
{
	
}

void battleActionState::draw(game* game) 
{

}