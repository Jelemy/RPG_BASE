#ifndef battleActionState_h
#define battleActionState_h

#include "gameState.h"
#include "SDL.h"
#include "SDL_image.h"
#include "action.h"
#include "battleState.h"

typedef std::vector<std::unique_ptr<action>> actions;

class battleActionState : public battleState
{
public:
	static battleDrawer* bDrawer;
	int currAction = 0;

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void handleSubEvents(battleState* battle);
	void update(game* game);
	void draw(game* game);

	bool isCreatedWithNew() const override {
        return true;
    }

	static battleActionState* createInstance(actions a) {
    	battleActionState* instance = new battleActionState(std::move(a));  // Only created once
    	return instance;
	}


private:
	actions actionList;
	battleActionState(actions a);
	//static battleActionState m_battleActionState;
	SDL_Surface* bg;

};

#endif