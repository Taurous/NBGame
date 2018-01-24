#pragma once

#include <allegro5\allegro.h>

#include "InputHandler.h"
#include "EventHandler.h"
#include "Window.h"
#include "DrawEngine.h"
//#include "SoundManager.h"
#include "StateManager.h"

#include "NodeManager.h"

const int ENGINE_SPEED = 60;

class Game
{
public:
	Game();
	~Game();

	int run();

private:
	axe::InputHandler m_input;
	axe::EventHandler m_events;
	axe::DrawEngine m_draw;
	axe::StateManager m_states;

	NodeManager m_nodes;

	axe::ResourceHandle<axe::Font> fn;
};

//Class MyClass
//Function myFunction
//Variable my_variable
//Constant MY_CONSTANT