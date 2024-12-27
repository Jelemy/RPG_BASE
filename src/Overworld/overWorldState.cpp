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

const char* mapFile = "assets/tileset.png";

/*
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
*/

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

std::vector<colliderComponent*> overWorldState::colliders;



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

	map::loadMap("assets/map.map", 20, 15);
	
	player.addComponent<transformComponent>(0, 0, 26, 18, 2);
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

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


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
	for (auto& e : enemies)
	{
		e->draw();
	}	

    SDL_RenderPresent(game::renderer);
}

void overWorldState::addCollider(colliderComponent* collider) {
    colliders.push_back(collider);
}

void overWorldState::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<tileComponent>(srcX, srcY, xpos, ypos, mapFile);
	tile.addGroup(groupMap);
}