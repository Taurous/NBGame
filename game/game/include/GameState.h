#pragma once

#include <axeLib\AbstractState.h>
#include "axeLib\StateManager.h"

class GameState : public axe::AbstractState
{
public:
	GameState(axe::StateManager &states, axe::InputHandler &input, axe::EventHandler &events, axe::DrawEngine &draw);
	virtual ~GameState();

	virtual void pause();
	virtual void resume();

	virtual void handleEvents();
	virtual void update();
	virtual void draw();

private:

};