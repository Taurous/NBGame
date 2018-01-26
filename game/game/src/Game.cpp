#include "Game.h"

#include "SplashState.h"

Game::Game() : m_nodes(1), m_events(ENGINE_SPEED)
{
	// Load settings before creating window to supply dimensions

	m_draw.createWindow(1280, 768, "The Game");
	m_draw.getWindow().registerForEvents(m_events.getEventQueue());

	m_draw.fonts.setPathToResources("res/fonts/");
	m_draw.bitmaps.setPathToResources("res/textures/");

	//fn = m_draw.fonts.getResource("24-VCR_OSD_MONO_1.ttf");
}

Game::~Game()
{
	// Save settings
}

void Game::run()
{
	bool redraw = true;

	//const int INPUT_LENGTH = 32;
	//m_input.enableTextInput(INPUT_LENGTH, true, false, false, false, true);
	//m_input.setInputString("Enter text here...");

	std::vector<axe::ResourceHandle<axe::Bitmap>> bitmaps;

	for (int i = 0; i < 1000; ++i)
	{
		bitmaps.push_back(m_draw.bitmaps.getResource("image2.png"));
	}

	m_states.changeState(std::unique_ptr<axe::AbstractState>(new SplashState(m_states, m_input, m_events, m_draw)));

	m_events.startTimer();
	while (m_states.running())
	{
		if (m_events.handleEvents())
		{
			m_input.getInput(m_events.getEvent());
			m_states.handleEvents();

			if (m_input.isKeyPressed(ALLEGRO_KEY_ESCAPE) || m_events.eventIs(ALLEGRO_EVENT_DISPLAY_CLOSE))
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
			else if (m_input.isKeyPressed(ALLEGRO_KEY_ENTER))
			{
				//m_nodes.handleInput(m_input.getTextInput());
				//m_input.clearInputString();

				//m_nodes.cleanNodeList();
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
			al_hold_bitmap_drawing(true);
			for (int j = 0; j < 6; ++j)
			{
				for (int i = 0; i < 10; ++i)
				{
					m_draw.drawBitmap(bitmaps[i], i * m_draw.bitmaps[bitmaps[i]]->getWidth(), j * m_draw.bitmaps[bitmaps[i]]->getWidth(), 0);
				}
			}
			al_hold_bitmap_drawing(false);

			m_states.draw();

			//m_draw.drawTextWithCursor(fn, al_map_rgb(0, 255, 0), 16, 16, axe::TEXT_JITTER, axe::m_secs(200), INPUT_LENGTH, m_input.getTextInput());

			m_draw.flipAndClear(al_map_rgb(0, 0, 0));
			redraw = false;
		}
	}
}