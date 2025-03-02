#ifndef battleActionState_h
#define battleActionState_h

#include "gameState.h"
#include "SDL.h"
#include "SDL_image.h"
#include "action.h"
#include "battleState.h"

typedef std::vector<std::unique_ptr<action>> actions;
enum battleFlowState
{
	WON, LOST, CONTINUE
};
class battleActionState : public battleState
{
public:
	int currAction = 0;

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void handleSubEvents(battleState* battle, game* game) override;
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
	battleFlowState battleCondition = CONTINUE;
	actions actionList;
	string currLine;
	battleActionState(actions a);
	bool checkPartyDead();
	bool checkEnemiesDead();
	void updateActionState();
	//static battleActionState m_battleActionState;
	SDL_Surface* bg;

};

#endif