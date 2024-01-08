#ifndef selectTargetState_h
#define selectTargetState_h

#include "battleState.h"

class selectTargetState : public battleState
{
public:
	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(battleState* b);
	void update(battleState* b);
	void draw(battleState* b);

	static selectTargetState* instance() {
		return &m_selectTargetState;
	}

protected:
	selectTargetState() { }

private:
	static selectTargetState m_selectTargetState;
};

#endif