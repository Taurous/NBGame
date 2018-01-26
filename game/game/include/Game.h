#pragma once

#include <allegro5\allegro.h>

#include "InputHandler.h"
#include "EventHandler.h"
#include "Window.h"
#include "DrawEngine.h"
//#include "SoundManager.h"
#include "StateManager.h"

const int ENGINE_SPEED = 60;

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	axe::InputHandler m_input;
	axe::EventHandler m_events;
	axe::DrawEngine m_draw;
	axe::StateManager m_states;
};

//Class MyClass
//Function myFunction
//Variable my_variable
//Constant MY_CONSTANT