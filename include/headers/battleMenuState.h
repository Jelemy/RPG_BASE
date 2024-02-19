#ifndef battleMenuState_h
#define battleMenuState_h

#include "gameState.h"
#include "SDL.h"
#include "SDL_image.h"
#include "action.h"
#include "battleGlobal.h"
#include "battleActionState.h"

class battleMenuState : public battleState
{
public:
	menuLayer currLayer = ACT;
    int actionSelect = 0;
    int artSelect = -1;
    int selectMove = 0;
	bool arts = false;
	bool bash = false;
	int optionMax = 1;

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(game* game);
	void handleSubEvents(battleState* battle) override;
	void update(game* game);
	void draw(game* game);

	static battleMenuState* instance() {
		return &m_battleMenuState;
	}

protected:
	battleMenuState() { }

private:
	std::vector<std::unique_ptr<action>> actionList;
	static battleMenuState m_battleMenuState;
	SDL_Surface* bg;
	void handleAct();
	void handleArt();
	void handleEnemy(battleState* battle);
	void handleAlly(battleState* battle);
	int findNextAlive(int index);
	int getNumAlive();

	// fill these in and feed to action
	int currPlayer = 0;
	int actionerIndex = 0;
	partyType actionParty;
	commands command;
	int commandIndex;
	int recipientIndex;
	eventType eType;




	

};

#endif