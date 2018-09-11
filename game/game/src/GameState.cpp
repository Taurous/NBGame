#include "GameState.h"

GameState::GameState(axe::StateManager & states, axe::InputHandler & input, axe::EventHandler & events, axe::DrawEngine & draw)
	: AbstractState(states, input, events, draw)
{

}

GameState::~GameState()
{
}

void GameState::pause()
{
}

void GameState::resume()
{
}

void GameState::handleEvents()
{
	if (m_input.isKeyPressed(ALLEGRO_KEY_SPACE))
	{
		m_states.quit();
	}
}

void GameState::update()
{
}

void GameState::draw()
{

}
