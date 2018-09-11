#pragma once

#include <allegro5\allegro.h>

#include <axeLib\InputHandler.h>
#include <axeLib\EventHandler.h>
#include <axeLib\DrawEngine.h>
#include <axeLib\StateManager.h>

#include <iostream>
#include <fstream>

#include "nlohmann\json.hpp"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	axe::InputHandler	m_input;
	axe::EventHandler	m_events;
	axe::DrawEngine		m_draw;
	axe::StateManager	m_states;

	nlohmann::json		m_settings;

	void defaultSettings();
	bool loadSettings(std::string file);
	bool saveSettings(std::string file);

	int m_screen_width;
	int m_screen_height;
};

//Class				MyClass
//Function			myFunction
//Variable			my_variable
//Member Variable	m_my_variable
//Constant			MY_CONSTANT