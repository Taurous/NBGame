#pragma once

#include <allegro5\allegro.h>

#include <axeLib\InputHandler.h>
#include <axeLib\EventHandler.h>
#include <axeLib\DrawEngine.h>
#include <axeLib\StateManager.h>

#include <iostream>

static const int ENGINE_SPEED = 60;

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