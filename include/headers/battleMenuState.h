#ifndef battleMenuState_h
#define battleMenuState_h

#include "gameState.h"
#include "SDL.h"
#include "SDL_image.h"
#include "action.h"

enum menuLayer
{
    ACT, ART
};

class battleMenuState : public gameState
{
public:
	static battleDrawer* bDrawer;
	static battleManager* bm;
	menuLayer currLayer = ACT;
    int actionSelect = 0;
    int artSelect = -1;
    int selectMove = 0;

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void update(game* game);
	void draw(game* game);

	static battleMenuState* instance() {
		return &m_battleMenuState;
	}

protected:
	battleMenuState() { }

private:
	static battleMenuState m_battleMenuState;
	SDL_Surface* bg;

};

#endif