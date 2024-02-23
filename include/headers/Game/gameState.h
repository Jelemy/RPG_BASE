#ifndef gameState_h
#define gameState_h

#include "game.h"

class gameState
{
public:
	virtual void init() = 0;
	virtual void clean() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(game* game) = 0;
	virtual void update(game* game) = 0;
	virtual void draw(game* game) = 0;

	void changeState(game* game, gameState* state) {
		game->changeState(state);
	}

protected:
	gameState() { }
};

#endif