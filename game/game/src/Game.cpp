#include "Game.h"

#include "SplashState.h"

#include <SettingsHandler.h>

Game::Game() : m_events(ENGINE_SPEED)
{
	int windowWidth = 1280;
	int windowHeight = 768;

	axe::SettingsHandler s;

	s.set("width", windowWidth);
	s.set("height", windowHeight);

	s.loadSettings(".settings");

	s.get("width", windowWidth);
	s.get("height", windowHeight);

	m_draw.createWindow(windowWidth, windowHeight, "The Game");
	m_draw.getWindow().registerForEvents(m_events.getEventQueue());

	m_draw.fonts.setPathToResources("res/fonts/");
	m_draw.bitmaps.setPathToResources("res/textures/");
	// Test change
}

Game::~Game()
{
	axe::SettingsHandler s;

	s.set("width", m_draw.getWindowWidth());
	s.set("height", m_draw.getWindowHeight());

	s.saveSettings(".settings");
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
				m_draw.bitmaps.removeUnreferencedResources();
				m_draw.fonts.removeUnreferencedResources();
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