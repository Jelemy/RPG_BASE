#ifndef enemyTurnState_h
#define enemyTurnState_h

#include "battleState.h"
#include "SDL.h"
#include "SDL_image.h"

class enemyTurnState : public battleState
{
public:
	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(battleState* b);
	void update(battleState* b);
	void draw(battleState* b);

	static enemyTurnState* instance() {
		return &m_enemyTurnState;
	}

protected:
	enemyTurnState() { }

private:
	static enemyTurnState m_enemyTurnState;
};

#endif