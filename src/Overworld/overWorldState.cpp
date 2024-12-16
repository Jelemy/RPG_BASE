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
#include <map.h>
#include <collision.h>

overWorldState overWorldState::m_overWorldState;

// Manager is a class that manages all the entities.
Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());
SDL_Event overWorldState:: event;
map* tileMap;

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());


std::vector<colliderComponent*> overWorldState::colliders;

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
	// error happening because we are readding componesnts everytime we go back to tis state:

	tile0.addComponent<tileComponent>(200, 200, 32, 32, 0);
	tile0.addComponent<colliderComponent>("water");
	tile1.addComponent<tileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<colliderComponent>("dirt");
	tile2.addComponent<tileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<colliderComponent>("grass");

	player.addComponent<transformComponent>(0, 0, 26, 18, 2);
	player.addComponent<spriteComponent>("assets/dawnsheet2.png", "player");
    player.addComponent<KeyboardController>();
	player.addComponent<colliderComponent>("player");

	wall.addComponent<transformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<spriteComponent>("assets/dirt.png", "non");
	wall.addComponent<colliderComponent>("wall");


    tileMap = new map();
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
	//player.getComponent<transformComponent>().position.Add(Vector2D(5, 0));

	for (auto cc : colliders)
	{
		collision::AABB(player.getComponent<colliderComponent>(), *cc);
	}
}

void overWorldState::draw(game* game) 
{
    SDL_RenderClear(game::renderer);
    //tileMap->drawMap();
	manager.draw();
    SDL_RenderPresent(game::renderer);
}

void overWorldState::addCollider(colliderComponent* collider) {
    colliders.push_back(collider);
}