
#ifndef titleState_h
#define titleState_h

#include "SDL.h"
#include "SDL_image.h"
#include "gameState.h"

class titleState : public gameState
{
public:
	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void update(game* game);
	void draw(game* game);

	static titleState* instance() {
		return &m_titleState;
	}

protected:
	titleState() { }

private:
	static titleState m_titleState;

	SDL_Surface* bg;
};

#endif