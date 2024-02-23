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
std::unordered_map<string, artInfo> artsInfo;
entities enemyParty;
entities playerParty;

void battleState::init()
{
	std::vector<std::unique_ptr<action>> initialActions;
	artInfo art1 = make_tuple("magic_damage", 3, 10, "Deals fire magic damage");
    artInfo art2 = make_tuple("physical_damage", 5, 10, "Deals light damage");
    artInfo art3 = make_tuple("heal", 5, 10, "Restores 10 HP");
    artsInfo.insert({{"Fire", art1},{"Mega Bash", art2}, {"Heal", art3}});

	// Adding actions to the list
	

	std::vector<std::string> arts1 = {"Fire", "Mega Bash"};
	std::vector<std::string> arts2 = {"Heal"};

	auto& party1(manager.addEntity());
	auto& party2(manager.addEntity());
	auto& enemy1(manager.addEntity());
	auto& enemy2(manager.addEntity());
	party1.addComponent<statsComponent>("party1", 30, 5, 20, 20, 10, 10, 16, 10, 10, 10, arts1);
	party2.addComponent<statsComponent>("party2", 30, 5, 20, 20, 10, 10, 15, 10, 10, 10, arts2);
	enemy1.addComponent<statsComponent>("enemy1", 10, 10, 20, 20, 9, 10, 8, 10, 10, 10, arts1);
	enemy2.addComponent<statsComponent>("enemy2", 10, 10, 20, 20, 8, 10, 11, 10, 10, 10, arts1);
	enemy1.addComponent<tSpriteComponent>("assets/fridgedonkey2.png", 130, 170);
    enemy2.addComponent<tSpriteComponent>("assets/fridgedonkey.png", 320, 170);
	playerParty = {&party1, &party2};
	enemyParty = {&enemy1, &enemy2};

	bManager = new battleManager();
	bDrawer = new battleDrawer();
	
	initialActions.push_back(std::make_unique<action>(BATTLESTART));

	battleActionState* nextState = battleActionState::createInstance(std::move(initialActions));

	this->changeBattleState(nextState);
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
	battleStates.back()->handleSubEvents(this, game);
	//battleStates.back()->handleEvents(game);

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
}

void battleState::update(game* game) 
{
	battleStates.back()->update(game);
}

void battleState::draw(game* game) 
{
	SDL_RenderClear(game::renderer);
	bDrawer->drawBG();
	bDrawer->drawEnemy();
	battleStates.back()->draw(game);
	SDL_RenderPresent(game::renderer);
}