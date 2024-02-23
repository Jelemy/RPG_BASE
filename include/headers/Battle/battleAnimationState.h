#ifndef battleAnimationState_h
#define battleAnimationState_h

#include "battleState.h"
#include "SDL.h"
#include "SDL_image.h"

class battleAnimationState : public battleState
{
public:
	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(battleState* b);
	void update(battleState* b);
	void draw(battleState* b);

	static battleAnimationState* instance() {
		return &m_battleAnimationState;
	}

protected:
	battleAnimationState() { }

private:
	static battleAnimationState m_battleAnimationState;
};

#endif