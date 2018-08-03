#include "MenuState.h"

#include "axeLib\StateManager.h"

MenuState::MenuState(axe::StateManager & states, axe::InputHandler & input, axe::EventHandler & events, axe::DrawEngine & draw)
	: AbstractState(states, input, events, draw), m_nodes(0)
{
	m_input.enableTextInput(INPUT_LENGTH, false, false, false, false, true);
	m_input.setInputString("Enter text here...");

	fn = m_draw.fonts.getResource("18-VCR_OSD_MONO_1.ttf");
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
		printf("\n");
		int current = m_nodes.getCurrentNodeID();
		int next = m_nodes.handleInput(m_input.getTextInput()); // Get next node id based on input

		if (next != -1) // -1 is an invalid argument, do not push
		{
			m_nodes.pushNode(next, current);
		}

		m_input.clearInputString();

		m_nodes.cleanNodeList();
	}
	else if (m_events.eventIs(axe::GUI_EVENT_BUTTON_PRESSED))
	{
		/*if (events.getEvent().user.data1 == button->getID())
		{

		}*/
	}
	else if (m_input.isKeyPressed(ALLEGRO_KEY_ESCAPE))
	{
		m_states.quit();
	}
}

void MenuState::update()
{
}

void MenuState::draw()
{
	int center_window_x = m_draw.getWindowWidth() / 2;
	int center_window_y = m_draw.getWindowHeight() / 2;

	m_draw.drawTextWithCursor(fn, al_map_rgb(0, 255, 0), center_window_x/2, center_window_y * 2 - 64, 0, axe::m_secs(200), INPUT_LENGTH, m_input.getTextInput());
}
