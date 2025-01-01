#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "gameState.h"
#include "battleManager.h"
#include "battleDrawer.h"
#include <unordered_map>
#include <tuple>
#include <vector>

class colliderComponent;

class overWorldState : public gameState
{
public:
	static battleManager* battle;
	static battleDrawer* bDrawer;
	static SDL_Event event;

    static SDL_Event& getEvent() {
        return event;
    }

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void update(game* game);
	void draw(game* game);

	static overWorldState* instance() {
		return &m_overWorldState;
	}

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders
	};

protected:
	overWorldState() { }

private:
	static overWorldState m_overWorldState;

	SDL_Surface* bg;
};