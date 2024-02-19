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

overWorldState overWorldState::m_overWorldState;

// Manager is a class that manages all the entities.
Manager manager;
entities playerParty;

// How you add an entity. auto& automatically assigns a variable type.
auto& entity(manager.addEntity());

void overWorldState::init()
{
    // ECS example implementation
    entity.addComponent<positionComponent>();
    entity.addComponent<spriteComponent>("assets/dawnWalk.png");

	// new

	// for purpose of testing: create party and enemy entities and add stats component
	// Load party and enemies into battle manager called battle
	// initialise first battle state: enemy encounter message
	auto& party1(manager.addEntity());
	auto& party2(manager.addEntity());
	auto& enemy1(manager.addEntity());
	auto& enemy2(manager.addEntity());

	std::vector<std::string> arts1 = {"Fire", "Mega Bash", "Heal"};
	std::vector<std::string> arts2 = {"Heal"};
    // make arts dictionary
	
	party1.addComponent<statsComponent>("party1", 30, 30, 20, 20, 10, 10, 16, 10, 10, 10, arts1);
	party2.addComponent<statsComponent>("party2", 30, 30, 20, 20, 10, 10, 15, 10, 10, 10, arts2);
	// new
	playerParty = {&party1, &party2};
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
}

void overWorldState::draw(game* game) 
{
    SDL_RenderClear(game::renderer);
    manager.draw();
    SDL_RenderPresent(game::renderer);

}