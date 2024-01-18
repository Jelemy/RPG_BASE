#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <overWorldState.h>
#include <battleState.h>
#include <battleActionState.h>
#include <global.h>
#include <battleGlobal.h>

battleState battleState::m_battleState;

battleManager* bManager;
battleDrawer* bDrawer;
entities enemyParty;

void battleState::init()
{
	std::vector<std::unique_ptr<action>> initialActions;

	// Adding actions to the list
	initialActions.push_back(std::make_unique<action>(BATTLESTART));
	initialActions.push_back(std::make_unique<action>(VICTORY));

	battleActionState* nextState = battleActionState::createInstance(std::move(initialActions));

	this->changeBattleState(nextState);
	std::cout << playerParty[0]->getComponent<statsComponent>().HP() << std::endl;

	std::vector<std::string> arts1 = {"Fire", "Mega Bash"};

	auto& enemy1(manager.addEntity());
	auto& enemy2(manager.addEntity());
	enemy1.addComponent<statsComponent>("enemy1", 100, 100, 20, 20, 9, 10, 8, 10, 10, 10, arts1);
	enemy2.addComponent<statsComponent>("enemy2", 100, 100, 20, 20, 8, 10, 11, 10, 10, 10, arts1);
	enemyParty = {&enemy1, &enemy2};

	bManager = new battleManager(playerParty, enemyParty);
	bDrawer = new battleDrawer(playerParty, enemyParty);

	//making it so that we make use of global variables instead of simply juts passing


	
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
						game->popState();
						break;

					case SDLK_ESCAPE:
						game->quit();
						break;
				}
				break;
		}
	}

	battleStates.back()->handleSubEvents(this);
}


void battleState::handleSubEvents(battleState* battle)
{
	
}
void battleState::update(game* game) 
{
	battleStates.back()->update(game);
}

void battleState::draw(game* game) 
{
	SDL_RenderClear(game::renderer);
	bDrawer->drawBG();
	bDrawer->drawMenu();
	bDrawer->drawSubMenu();
	bDrawer->drawPartyBox();
	bDrawer->drawMessage();
	SDL_RenderPresent(game::renderer);
}