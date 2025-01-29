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
	// declare initial actions list with initial battle dialogue
	std::vector<std::unique_ptr<action>> initialActions;

	// initialise arts art tuple (<art type>, <art cost>, <art base dmg/heal>, <art description>)
	artInfo art1 = make_tuple("magic_damage", 3, 10, "Deals fire magic damage");
    artInfo art2 = make_tuple("physical_damage", 5, 10, "Deals light damage");
    artInfo art3 = make_tuple("heal", 5, 10, "Restores 10 HP");
    artsInfo.insert({{"Fire", art1},{"Mega Bash", art2}, {"Heal", art3}});

	// prepare sets of arts to give to entities
	std::vector<std::string> arts1 = {"Fire", "Mega Bash"};
	std::vector<std::string> arts2 = {"Heal"};

	// Create battle entities and apply stats and sprites
	auto& party1(manager.addEntity());
	auto& party2(manager.addEntity());
	auto& enemy1(manager.addEntity());
	auto& enemy2(manager.addEntity());
	party1.addComponent<statsComponent>("Dawn", 30, 30, 20, 20, 10, 10, 16, 10, 10, 10, arts1);
	party2.addComponent<statsComponent>("Ghost", 30, 30, 20, 20, 10, 10, 15, 10, 10, 10, arts2);
	enemy1.addComponent<statsComponent>("Fridge Donkey A", 30, 30, 20, 20, 9, 10, 8, 10, 10, 10, arts1);
	enemy2.addComponent<statsComponent>("Fridge Donkey B", 30, 30, 20, 20, 8, 10, 11, 10, 10, 10, arts1);
	enemy1.addComponent<bSpriteComponent>("assets/fridgedonkey2.png", 130, 170);
    enemy2.addComponent<bSpriteComponent>("assets/fridgedonkey.png", 320, 170);
	playerParty = {&party1, &party2};
	enemyParty = {&enemy1, &enemy2};

	// Initialise battle manager, which deals with action executions
	bManager = new battleManager();
	// Initialise battle drawer which puts things to screen
	bDrawer = new battleDrawer();
	// Indicate starting dialogue for battle
	initialActions.push_back(std::make_unique<action>(BATTLESTART));


	// Change to battle action sub state.
	battleActionState* nextState = battleActionState::createInstance(std::move(initialActions));
	this->changeBattleState(nextState);
	
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
	// let current sub battle state handle events
	battleStates.back()->handleSubEvents(this, game);
	
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