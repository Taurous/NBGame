#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

int Game::init()
{
	//Init all systems
#ifndef _DEBUG
	axe::setOutputFile("log.txt");
#endif

	if (!al_init())
	{
		return 1;
	}

	m_ih = new axe::InputHandler();

	m_eh = new axe::EventHandler();
	m_eh->init(_ENGINE_SPEED);

	m_wind = new axe::Window(640, 480, "Nicest Boy Studios - The Game");
	m_wind->registerForEvents(m_eh->getEventQueue());

	m_de = new axe::DrawEngine();
	m_de->init(m_wind);

	m_de->fonts.setPathToResources("res/fonts/");
	m_de->bitmaps.setPathToResources("res/textures/");

	return 0;
}

int Game::run()
{
	bool exit = false;
	bool redraw = true;

	m_eh->startTimer();
	while (!exit)
	{
		if (m_eh->handleEvents())
		{
			m_ih->getInput(m_eh->getEvent());

			if (m_ih->isKeyPressed(ALLEGRO_KEY_ESCAPE) || m_eh->eventIs(ALLEGRO_EVENT_DISPLAY_CLOSE))
			{
				exit = true;
			}
			else if (m_eh->eventIs(ALLEGRO_EVENT_TIMER))
			{
				redraw = true;
			}
			else if (m_eh->eventIs(axe::GUI_EVENT_BUTTON_PRESSED))
			{
				/*if (events.getEvent().user.data1 == button->getID())
				{

				}*/
			}
		}

		if (m_eh->eventQueueEmpty() && redraw)
		{
			m_de->flipAndClear(al_map_rgb(0, 0, 0));
			redraw = false;
		}
	}

	return 0;
}

void Game::destroy()
{
	delete m_de;
	delete m_wind;
	delete m_eh;
	delete m_ih;
}