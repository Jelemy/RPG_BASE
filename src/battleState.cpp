#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <overWorldState.h>
#include <battleState.h>


battleState battleState::m_battleState;

Manager manager1;
battleManager* battleState::battle = nullptr;
battleDrawer* battleState::bDrawer = nullptr;

void battleState::init()
{

	// for purpose of testing: create party and enemy entities and add stats component
	// Load party and enemies into battle manager called battle
	// initialise first battle state: enemy encounter message
	auto& party1(manager1.addEntity());
	auto& party2(manager1.addEntity());
	auto& enemy1(manager1.addEntity());
	auto& enemy2(manager1.addEntity());

	auto& uiMenu(manager1.addEntity());
	auto& uiSubMenu(manager1.addEntity());
	auto& uiPartyBox1(manager1.addEntity());
	auto& uiPartyBox2(manager1.addEntity());
	auto& uiArrow(manager1.addEntity());
	auto& uiMessage(manager1.addEntity());
	auto& bg(manager1.addEntity());

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
	uiArrow.addComponent<tSpriteComponent>("assets/arrow.png", 50, 170);
	uiMessage.addComponent<tSpriteComponent>("assets/dialoguebox.png", 121, 22);
	bg.addComponent<tSpriteComponent>("assets/plain.png", 0, 0);

	std::vector<Entity*> playerParty = {&party1, &party2};
	std::vector<Entity*> enemyParty = {&enemy1, &enemy2};
	std::vector<Entity*> ui = {&uiMenu, &uiSubMenu, &uiPartyBox1, &uiPartyBox2, &uiMessage, &bg, &uiArrow};

	//std::cout << enemyParty[1]->getComponent<statsComponent>().trns() << std::endl;

	battle = new battleManager(playerParty, enemyParty);
	bDrawer = new battleDrawer(playerParty, enemyParty, ui);
/*
	std::cout << battle->getTurn()->getComponent<statsComponent>().spd() << std::endl;
	std::cout << enemy2.getComponent<statsComponent>().HP() << std::endl;
	std::cout << party1.getComponent<statsComponent>().MP() << std::endl;
	std::cout << party1.getComponent<statsComponent>().trns() << std::endl;
	std::cout << party2.getComponent<statsComponent>().trns() << std::endl;
	battle->performArt(0, 1);
	std::cout << battle->getTurn()->getComponent<statsComponent>().spd() << std::endl;
	battle->performAttack(1);
	std::cout << enemy2.getComponent<statsComponent>().HP() << std::endl;
	std::cout << party1.getComponent<statsComponent>().MP() << std::endl;
	std::cout << party1.getComponent<statsComponent>().trns() << std::endl;
	std::cout << party2.getComponent<statsComponent>().trns() << std::endl;
*/

}

void battleState::changeBattleState(battleState* state) 
{
	// cleanup the current state
	if ( !battleStates.empty() ) {
		battleStates.back()->clean();
		battleStates.pop_back();
	}

	// store and init the new state
	battleStates.push_back(state);
	battleStates.back()->init();
}

// Pushes a new state into the battleStates list
void battleState::pushBattleState(battleState* state)
{
	// pause current state
	if ( !battleStates.empty() ) {
		battleStates.back()->pause();
	}

	// store and init the new state
	battleStates.push_back(state);
	battleStates.back()->init();
}

// pop's off the current state
void battleState::popBattleState()
{
	// cleanup the current state
	if ( !battleStates.empty() ) {
		battleStates.back()->clean();
		battleStates.pop_back();
	}

	// resume previous state
	if ( !battleStates.empty() ) {
		battleStates.back()->resume();
	}
}
void battleState::clean()
{
	printf("battleState Cleanup\n");
	delete battle;
	delete bDrawer;
}

void battleState::pause()
{
	printf("battleState Pause\n");
}

void battleState::resume()
{
	printf("battleState Resume\n");
}

void battleState::handleEvents(game* game)
{
	// let current battle state handle events
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
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

void battleState::update(game* game) 
{
}

void battleState::draw(game* game) 
{
	SDL_RenderClear(game::renderer);
	bDrawer->drawBG();
	bDrawer->drawMenu();
	bDrawer->drawSubMenu();
	bDrawer->drawPartyBox();
	bDrawer->drawMessage();
	//bDrawer->drawSelect();
	SDL_RenderPresent(game::renderer);
}