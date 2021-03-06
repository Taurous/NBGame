#pragma once

#include <axeLib\AbstractState.h>
#include "axeLib\StateManager.h"

class MenuState : public axe::AbstractState
{
public:
	MenuState(axe::StateManager &states, axe::InputHandler &input, axe::EventHandler &events, axe::DrawEngine &draw);
	virtual ~MenuState();

	virtual void pause();
	virtual void resume();

	virtual void handleEvents();
	virtual void update();
	virtual void draw();

private:
	axe::ResourceHandle<axe::Font> fn;
};