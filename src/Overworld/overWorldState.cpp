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



void overWorldState::init()
{

	// initialise map with tile atlas, tile scale factor and tile dimensions
	// use matrix in external file to create tile layout
	tileMap = new map(mapFile, 1, 32);
	tileMap->loadMap("assets/map.map", 20, 15);

    // Check if player entity already has components
    if (!player.hasComponent<transformComponent>()) {
		// create and initialise player entity.
		// give it a sprite, controller input and make it collidable.
		// Add it to group (for render layers)
        player.addComponent<transformComponent>(100, 288, 26, 18, 2);
        player.addComponent<spriteComponent>("assets/dawnsheet2.png", "player");
        player.addComponent<KeyboardController>();
        player.addComponent<colliderComponent>("player");
        player.addGroup(groupPlayers);
    } 
    else {
        // Reset player position if components already exist
        player.getComponent<transformComponent>().position.x = 100;
        player.getComponent<transformComponent>().position.y = 288;
		player.getComponent<transformComponent>().velocity.x = 0;
		player.getComponent<transformComponent>().velocity.y = 0;

    }

}

void overWorldState::clean()
{
	//printf("overWorldState Cleanup\n");
}

void overWorldState::pause()
{
	//printf("overWorldState Pause\n");
}

void overWorldState::resume()
{
	//printf("overWorldState Resume\n");
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
	Vector2D playerPos = player.getComponent<transformComponent>().position;
	if (playerPos.x > 640) {
		game->changeState( battleState::instance() );
	}

}

void overWorldState::update(game* game) 
{
    // Get player's collider box and xy position
    SDL_Rect& playerCol = player.getComponent<colliderComponent>().collider;
    Vector2D& playerPos = player.getComponent<transformComponent>().position;

    // Store the previous position
    Vector2D prevPos = playerPos;

    // Update all entities
    manager.refresh();
    manager.update();

    // Check collision along the X-axis
    playerPos.x += player.getComponent<transformComponent>().velocity.x;
    playerCol.x = static_cast<int>(playerPos.x);

    for (auto c : colliders)
    {
        SDL_Rect cCol = c->getComponent<colliderComponent>().collider;
        if (collision::AABB(cCol, playerCol))
        {
            // Collision detected on the X-axis, revert X movement
            playerPos.x = prevPos.x;
            playerCol.x = static_cast<int>(playerPos.x);
            break;
        }
    }

    // Check collision along the Y-axis
    playerPos.y += player.getComponent<transformComponent>().velocity.y;
    playerCol.y = static_cast<int>(playerPos.y) + 20;

    for (auto c : colliders)
    {
        SDL_Rect cCol = c->getComponent<colliderComponent>().collider;
        if (collision::AABB(cCol, playerCol))
        {
            // Collision detected on the Y-axis, revert Y movement
            playerPos.y = prevPos.y;
            playerCol.y = static_cast<int>(playerPos.y) + 20;
            break;
        }
    }
}




void overWorldState::draw(game* game) 
{
    SDL_RenderClear(game::renderer);
	// draw tiles
	for (auto& t : tiles)
	{
		t->draw();
	}
	// draw player
	for (auto& p : players)
	{
		p->draw();
	}


    SDL_RenderPresent(game::renderer);
}