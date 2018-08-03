#include "Game.h"

#include <fstream>
#include "nlohmann\json.hpp"

#include "SplashState.h"

Game::Game() : m_events(ENGINE_SPEED)
{
	int windowWidth = 1280; // Default Window Size
	int windowHeight = 768;

	nlohmann::json j;

	std::ifstream in_file("settings.json");

	if (in_file.is_open())
	{
		in_file >> j;

		if (j.find("width") != j.end())
		{
			windowWidth = j["width"];
		}
		if (j.find("width") != j.end())
		{
			windowHeight = j["height"];
		}

		in_file.close();
	}
	m_draw.createWindow(windowWidth, windowHeight, "The Game");
	m_draw.getWindow().registerForEvents(m_events.getEventQueue());

	m_draw.fonts.setPathToResources("res/fonts/");
	m_draw.bitmaps.setPathToResources("res/textures/");
	// Test change

}

Game::~Game()
{
	nlohmann::json j;

	std::ofstream out_file("settings.json");

	if (out_file.is_open())
	{
		j["width"] = m_draw.getWindowWidth();
		j["height"] = m_draw.getWindowHeight();
		
		out_file << std::setw(4) << j;

		out_file.close();
	}
}

void Game::run()
{
	bool redraw = true;

	m_states.changeState(std::unique_ptr<axe::AbstractState>(new SplashState(m_states, m_input, m_events, m_draw)));

	m_events.startTimer();
	while (m_states.running())
	{
		if (m_events.handleEvents())
		{
			m_input.getInput(m_events.getEvent());
			m_states.handleEvents();

			if (m_events.eventIs(ALLEGRO_EVENT_DISPLAY_CLOSE))
			{
				m_states.quit();
			}
			else if (m_events.eventIs(ALLEGRO_EVENT_TIMER))
			{
				m_states.update();
				redraw = true;
			}
		}

		if (m_events.eventQueueEmpty() && redraw)
		{
			m_states.draw();

			m_draw.flipAndClear(al_map_rgb(0, 0, 0));
			redraw = false;
		}

		m_states.cleanStates();
	}
}