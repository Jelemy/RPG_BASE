#include <stdio.h>

#include <game.h>
#include <gameState.h>
#include <overWorldState.h>
#include <battleState.h>
#include <battleActionState.h>


battleState battleState::m_battleState;

Manager manager1;
battleManager* battleState::battle = nullptr;
battleDrawer* battleState::bDrawer = nullptr;

void battleState::init()
{
	this->changeBattleState(battleActionState::instance());
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
						game->changeState( overWorldState::instance() );
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
	//SDL_RenderClear(game::renderer);
	battleStates.back()->draw(game);
	//SDL_RenderPresent(game::renderer);
}