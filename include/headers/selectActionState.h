#ifndef selectActionState_h
#define selectActionState_h

#include "gameState.h"
#include "SDL.h"
#include "SDL_image.h"


class selectActionState : public gameState
{
public:

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(gameState* game);
	void update(gameState* game);
	void draw(gameState* game);

	static selectActionState* instance() {
		return &m_selectActionState;
	}

protected:
	selectActionState() { }

private:
	static selectActionState m_selectActionState;

	SDL_Surface* bg;
};

#endif