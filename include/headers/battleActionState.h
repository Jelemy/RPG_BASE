#ifndef battleActionState_h
#define battleActionState_h

#include "gameState.h"
#include "SDL.h"
#include "SDL_image.h"
#include "action.h"
#include "battleState.h"

typedef std::vector<action*> actions;

class battleActionState : public battleState
{
public:
	static battleDrawer* bDrawer;
	static actions actionList;
	int currAction = 0;

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void handleSubEvents(battleState* battle);
	void update(game* game);
	void draw(game* game);

	static battleActionState* instance() {
		return &m_battleActionState;
	}

protected:
	battleActionState() { }

private:
	static battleActionState m_battleActionState;
	SDL_Surface* bg;

};

#endif