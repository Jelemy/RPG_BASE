
#ifndef battleState_h
#define battleState_h

#include "SDL.h"
#include "SDL_image.h"
#include "gameState.h"
#include "battleManager.h"
#include "battleDrawer.h"
#include <unordered_map>
#include <tuple>

//typedef tuple<string, int, int, string> artInfo;
class battleManager;
class battleDrawer;

class battleState : public gameState
{
public:
	//static std::unordered_map<string, artInfo> artsInfo;
	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void handleSubEvents(battleState* battle);
	void update(game* game);
	void draw(game* game);

	static battleState* instance() {
		return &m_battleState;
	}

	virtual bool isCreatedWithNew() const {
        return false;  // Override in derived classes as needed
    }

	void changeBattleState(battleState* state);
	void pushBattleState(battleState* state);
	void popBattleState();

protected:
	battleState() { }

private:
	static battleState m_battleState;
	vector<battleState*> battleStates;
	SDL_Surface* bg;
};

#endif