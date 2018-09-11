#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState(axe::StateManager & states, axe::InputHandler & input, axe::EventHandler & events, axe::DrawEngine & draw)
	: AbstractState(states, input, events, draw)
{
	fn = m_draw.fonts.getResource("22-VCR_OSD_MONO_1.ttf");
}

MenuState::~MenuState()
{
}

void MenuState::pause()
{
}

void MenuState::resume()
{
}

void MenuState::handleEvents()
{
	if (m_input.isKeyPressed(ALLEGRO_KEY_ENTER))
	{
		m_states.changeState(std::unique_ptr<AbstractState>(new GameState(m_states, m_input, m_events, m_draw)));
	}
	else if (m_events.eventIs(axe::GUI_EVENT_BUTTON_PRESSED))
	{
		/*if (events.getEvent().user.data1 == button->getID())
		{

		}*/
	}
}

void MenuState::update()
{
}

void MenuState::draw()
{
	int center_window_x = m_draw.getWindowWidth() / 2;

	m_draw.drawText(fn, al_map_rgb(255, 0, 0), center_window_x, m_draw.getWindowHeight()*0.75, ALLEGRO_ALIGN_CENTER, "Press Enter");
}
