#include "Game.h"
#include "SplashState.h"

const int TICKS_PER_SECOND = 30;

void Game::defaultSettings()
{
	m_settings["width"] = 1280;
	m_settings["height"] = 720;
}

bool Game::loadSettings(std::string file)
{
	std::ifstream in_file(file);

	if (in_file.is_open())
	{
		in_file >> m_settings;

		in_file.close();
	}
	else return false;

	return true;
}

bool Game::saveSettings(std::string file)
{
	std::ofstream out_file(file);

	if (out_file.is_open())
	{
		m_settings["width"] = m_draw.getWindowWidth();
		m_settings["height"] = m_draw.getWindowHeight();

		out_file << std::setw(4) << m_settings;

		out_file.close();
	}
	else return false;

	return true;
}

Game::Game() : m_events(TICKS_PER_SECOND)
{
	defaultSettings();
	loadSettings("settings.json");

	m_draw.createWindow(m_settings["width"], m_settings["height"], "The Game");
	m_draw.getWindow().registerForEvents(m_events.getEventQueue());

	m_draw.fonts.setPathToResources("res/fonts/");
	m_draw.bitmaps.setPathToResources("res/textures/");
}

Game::~Game()
{
	saveSettings("settings.json");
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