#include "Game.h"

Game::Game() : m_nodes(1)
{
#ifndef _DEBUG
	axe::setOutputFile("log.txt");
#endif
}

Game::~Game()
{

}

int Game::init()
{
	

	m_events.init(ENGINE_SPEED);

	if (!m_draw.createWindow(640, 480, "The Game"))
	{
		return 2;
	}

	m_draw.getWindow().registerForEvents(m_events.getEventQueue());

	m_draw.fonts.setPathToResources("res/fonts/");
	m_draw.bitmaps.setPathToResources("res/textures/");

	fn = m_draw.fonts.getResource("24-VCR_OSD_MONO_1.ttf");

	return 0;
}

int Game::run()
{
	bool exit = false;
	bool redraw = true;
	std::string in_string;

	m_input.setInputString(in_string, 30, axe::INPUT_ALLOW_SPACE | axe::INPUT_ALLOW_NUMBERS);

	m_events.startTimer();
	while (!exit)
	{
		if (m_events.handleEvents())
		{
			m_input.getInput(m_events.getEvent());

			if (m_input.isKeyPressed(ALLEGRO_KEY_ESCAPE) || m_events.eventIs(ALLEGRO_EVENT_DISPLAY_CLOSE))
			{
				exit = true;
			}
			else if (m_events.eventIs(ALLEGRO_EVENT_TIMER))
			{
				redraw = true;
			}
			else if (m_input.isKeyPressed(ALLEGRO_KEY_ENTER))
			{
				m_nodes.handleInput(in_string);
				m_input.clearInputString();

				m_nodes.cleanNodeList();
			}
			else if (m_events.eventIs(axe::GUI_EVENT_BUTTON_PRESSED))
			{
				/*if (events.getEvent().user.data1 == button->getID())
				{

				}*/
			}
		}

		if (m_events.eventQueueEmpty() && redraw)
		{
			m_draw.drawTextWithCursor(fn, al_map_rgb(0, 255, 0), 16, 16, 0, axe::m_secs(100), 30, in_string);

			m_draw.flipAndClear(al_map_rgb(0, 0, 0));
			redraw = false;
		}
	}

	return 0;
}

void Game::destroy()
{

}