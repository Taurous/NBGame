#include "StateManager.h"

using namespace axe;

StateManager::StateManager() : v_draw_all(false), v_running(true), v_res(false) {}

void StateManager::cleanUp()
{
	while (!states.empty()) {
		states.back()->cleanUp();
		delete states.back();
		states.pop_back();
	}
}

void StateManager::changeState(AbstractState *state)
{
	if (!states.empty()) {
		deadStates.push_back(states.back());
		states.pop_back();
	}

	states.push_back(state);
	states.back()->init();
}

void StateManager::pushState(AbstractState *state)
{
	if (!states.empty()) {
		states.back()->pause();
	}

	states.push_back(state);
	states.back()->init();
}

void StateManager::popState()
{
	if (!states.empty()) {
		deadStates.push_back(states.back());
		states.pop_back();
		if (states.empty())
		{
			axe::log(axe::LOGGER_WARNING, "Trying to pop states, no states exist.\n");
		}
		else states.back()->resume();
	}
}
void StateManager::popState(int _FLAG, AbstractState *st)
{
	if (!states.empty()) {
		deadStates.push_back(states.back());
		states.pop_back();

		switch (_FLAG)
		{
		case STATE_CHANGE:
			changeState(st);
			break;
		case STATE_PUSH:
			pushState(st);
			break;
		case STATE_POP:
			popState();
			break;
		default:
			axe::log(LOGGER_ERROR, "Incorrect flag pass to popState()! Destroying state.\n");
			st->cleanUp();
			delete st;
			break;
		}
	}
}

void StateManager::handleEvents(InputHandler &input, EventHandler &events)
{
	states.back()->handleEvents(input, events);
}

void StateManager::update(InputHandler &input)
{
	states.back()->update(input);
}

void StateManager::draw(DrawEngine &draw)
{
	if (v_draw_all)
	{
		for (AbstractState *s : states) //Draw All!
		{
			s->draw(draw);
		}
	}
	else states.back()->draw(draw); // Draw Back!
}

void StateManager::cleanStates()
{
	while (!deadStates.empty())
	{
		deadStates.back()->cleanUp();
		delete deadStates.back();
		deadStates.pop_back();
	}
}