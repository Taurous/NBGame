#include "..\include\MenuState.h"

#include "StateManager.h"

MenuState::MenuState(axe::StateManager & states, axe::InputHandler & input, axe::EventHandler & events, axe::DrawEngine & draw)
	: AbstractState(states, input, events, draw), m_nodes(1)
{
	m_input.enableTextInput(INPUT_LENGTH, true, false, false, false, true);
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
		m_nodes.handleInput(m_input.getTextInput());
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
	m_draw.drawTextWithCursor(fn, al_map_rgb(0, 255, 0), 16, 16, 0, axe::m_secs(200), INPUT_LENGTH, m_input.getTextInput());
}
