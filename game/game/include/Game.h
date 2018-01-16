#pragma once

#include <allegro5\allegro.h>

#include "InputHandler.h"
#include "EventHandler.h"
#include "Window.h"
#include "DrawEngine.h"
//#include "SoundManager.h"
#include "StateManager.h"

const int _ENGINE_SPEED = 60;

class Game
{
public:
	Game();
	~Game();

	int init();
	int run();
	void destroy();

private:
	axe::InputHandler *m_ih;
	axe::EventHandler *m_eh;
	axe::Window *m_wind;
	axe::DrawEngine *m_de;
	axe::StateManager m_sm;
};

