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
SDL_Event overWorldState:: event;
map* tileMap;

const char* mapFile = "assets/tileset.png";

//auto& tiles(manager.getGroup(groupMap));
//auto& players(manager.getGroup(groupPlayers));


void overWorldState::init()
{
	// error happening because we are readding componesnts everytime we go back to tis state:

/*
	tile0.addComponent<tileComponent>(200, 200, 32, 32, 0);
	tile0.addComponent<colliderComponent>("water");
	tile1.addComponent<tileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<colliderComponent>("dirt");
	tile2.addComponent<tileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<colliderComponent>("grass");
*/
	tileMap = new map(mapFile, 1, 32);

	tileMap->loadMap("assets/map.map", 20, 15);
	
	player.addComponent<transformComponent>(100, 288, 26, 18, 2);
	player.addComponent<spriteComponent>("assets/dawnsheet2.png", "player");
    player.addComponent<KeyboardController>();
	player.addComponent<colliderComponent>("player");
	player.addGroup(groupPlayers);
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

auto& tiles(manager.getGroup(overWorldState::groupMap));
auto& players(manager.getGroup(overWorldState::groupPlayers));
auto& colliders(manager.getGroup(overWorldState::groupColliders));

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

	SDL_Rect playerCol = player.getComponent<colliderComponent>().collider;
	Vector2D playerPos = player.getComponent<transformComponent>().position;


	manager.refresh();
	manager.update();

	for (auto c : colliders)
	{
		SDL_Rect cCol = c->getComponent<colliderComponent>().collider;
		if (collision::AABB(cCol, playerCol))
		{
			player.getComponent<transformComponent>().position = playerPos;
		}
	}
}


void overWorldState::draw(game* game) 
{
    SDL_RenderClear(game::renderer);
    //tileMap->drawMap();
	//manager.draw();
	for (auto& t : tiles)
	{
		t->draw();
	}
	
	for (auto& p : players)
	{
		p->draw();
	}


    SDL_RenderPresent(game::renderer);
}