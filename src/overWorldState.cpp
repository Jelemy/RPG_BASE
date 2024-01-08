#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <overWorldState.h>
#include <battleActionState.h>
#include <battleMenuState.h>
#include <action.h>
#include <ECS.h>
#include <components.h>

overWorldState overWorldState::m_overWorldState;

// Manager is a class that manages all the entities.
Manager manager;

// new
Manager manager3;
battleManager* overWorldState::battle = nullptr;
battleDrawer* overWorldState::bDrawer = nullptr;
std::vector<action*> battleActionState::actionList = {new action(BATTLESTART), new action(VICTORY)};
battleDrawer* battleActionState::bDrawer = overWorldState::bDrawer;
battleManager* action::bm = overWorldState::battle;
battleManager* battleMenuState::bm = overWorldState::battle;
// new

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
	auto& party1(manager3.addEntity());
	auto& party2(manager3.addEntity());
	auto& enemy1(manager3.addEntity());
	auto& enemy2(manager3.addEntity());

	auto& uiMenu(manager3.addEntity());
	auto& uiSubMenu(manager3.addEntity());
	auto& uiPartyBox1(manager3.addEntity());
	auto& uiPartyBox2(manager3.addEntity());
	auto& uiArrow(manager3.addEntity());
	auto& uiMessage(manager3.addEntity());
	auto& bg(manager3.addEntity());

	std::vector<std::string> arts1 = {"Fire", "Mega Bash"};
	std::vector<std::string> arts2 = {"Heal"};
    // make arts dictionary
	


	party1.addComponent<statsComponent>("party1", 100, 100, 20, 20, 10, 10, 16, 10, 10, 10, arts1);
	party2.addComponent<statsComponent>("party2", 100, 100, 20, 20, 10, 10, 15, 10, 10, 10, arts2);
	enemy1.addComponent<statsComponent>("enemy1", 100, 100, 20, 20, 9, 10, 8, 10, 10, 10, arts1);
	enemy2.addComponent<statsComponent>("enemy2", 100, 100, 20, 20, 8, 10, 11, 10, 10, 10, arts1);

	uiMenu.addComponent<tSpriteComponent>("assets/menubox.png", 40, 150);
	uiSubMenu.addComponent<tSpriteComponent>("assets/menuboxsub.png", 147, 150);
	uiPartyBox1.addComponent<tSpriteComponent>("assets/partyBox2.png", 147, 420);
	uiPartyBox2.addComponent<tSpriteComponent>("assets/partyBox2.png", 330, 420);
	uiArrow.addComponent<tSpriteComponent>("assets/arrow.png", 50, 193);
	uiMessage.addComponent<tSpriteComponent>("assets/dialoguebox.png", 121, 22);
	bg.addComponent<tSpriteComponent>("assets/plain.png", 0, 0);

	std::vector<Entity*> playerParty = {&party1, &party2};
	std::vector<Entity*> enemyParty = {&enemy1, &enemy2};
	std::vector<Entity*> ui = {&uiMenu, &uiSubMenu, &uiPartyBox1, &uiPartyBox2, &uiMessage, &bg, &uiArrow};

	//std::cout << enemyParty[1]->getComponent<statsComponent>().trns() << std::endl;

	battle = new battleManager(playerParty, enemyParty);
	battleActionState::bDrawer = new battleDrawer(playerParty, enemyParty, ui);
	battleMenuState::bm = battle;

	// new
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
						game->changeState( battleActionState::instance() );
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