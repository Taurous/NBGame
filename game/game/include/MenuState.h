#pragma once

#include <AbstractState.h>
#include "NodeManager.h"

#include <string>

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
	const int INPUT_LENGTH = 32;

	NodeManager m_nodes;

	axe::ResourceHandle<axe::Font> fn;
};