#include "InputHandler.h"

using namespace axe;

const unsigned char letters[] = {
	  0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
	'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
	'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	')', '!', '@', '#', '$', '%', '^', '&', '*', '(' // Must fix %
};

const m_secs BACKSPACE_WORD_DELETE_TIME(100); //Time between word deletes
const m_secs BACKSPACE_CHAR_DELETE_TIME(30); //Time between character deletes
const m_secs BACKSPACE_WAIT_TIME(400); //Time after press before continuous deleting

void deleteCharacter(std::string &str)
{
	if (!str.empty())
	{
		str.pop_back();
	}
}
void deleteWord(std::string &str)
{
	while (true)
	{
		if (str.empty()) break;

		if (str.back() != ' ' && str.back() != '\n')
		{
			str.pop_back();
		}
		else
		{
			str.pop_back();
			break;
		}
	}
}

InputHandler::InputHandler()
	: m_input_flags(0)
	, m_mod_flags(0)
	, backspace(false)
	, input_string(nullptr)
	, max_input_length(0)
	, backspace_wait(BACKSPACE_WAIT_TIME)
{
	al_install_keyboard();
	al_install_mouse();

	al_get_mouse_state(&prev_mouse_state);
	cur_mouse_state = prev_mouse_state;
	al_get_keyboard_state(&prev_key_state);
	cur_key_state = prev_key_state;

	axe::log(LOGGER_MESSAGE, "InputHandler initialized\n");
}

InputHandler::~InputHandler()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

void InputHandler::stringPushBack(char c)
{
	if (input_string->size() < max_input_length) input_string->push_back(c);
}

void InputHandler::getInput(const ALLEGRO_EVENT &ev)
{
	prev_mouse_state = cur_mouse_state;
	al_get_mouse_state(&cur_mouse_state);

	prev_key_state = cur_key_state;
	al_get_keyboard_state(&cur_key_state);

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		// Get Modifiers Pressed
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_LSHIFT:
		case ALLEGRO_KEY_RSHIFT:
			m_mod_flags.set(MOD_SHIFT, true); // Doesn't work.
			setBit(m_mod_flags, MOD_SHIFT, true);
			setBit(m_mod_flags, MOD_NONE, false);
			break;
		case ALLEGRO_KEY_ALT:
			setBit(m_mod_flags, MOD_ALT, true);
			setBit(m_mod_flags, MOD_NONE, false);
			break;
		case ALLEGRO_KEY_LCTRL:
		case ALLEGRO_KEY_RCTRL:
			setBit(m_mod_flags, MOD_CTRL, true);
			setBit(m_mod_flags, MOD_NONE, false);
			break;
		case ALLEGRO_KEY_BACKSPACE:
			backspace = true;
			backspace_wait = m_secs(0);
			timer.start();
			if (m_mod_flags & MOD_CTRL) deleteWord(*input_string);
			else deleteCharacter(*input_string);
			break;
		default:
			break;
		};

		/*
		Handle Text Input
		Not completely done, some characters missing, and some issues still present.
		*/

		handleTextInput(ev);
	}

	// Clear Modifiers Released
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_LSHIFT:
		case ALLEGRO_KEY_RSHIFT:
			setBit(m_mod_flags, MOD_SHIFT, false);
			break;
		case ALLEGRO_KEY_ALT:
			setBit(m_mod_flags, MOD_ALT, false);
			break;
		case ALLEGRO_KEY_LCTRL:
		case ALLEGRO_KEY_RCTRL:
			setBit(m_mod_flags, MOD_CTRL, false);
			break;
		case ALLEGRO_KEY_BACKSPACE:
			backspace = false;
			break;
		default:
			break;
		};
		if (!m_mod_flags) m_mod_flags = MOD_NONE;
	}

	if (backspace && input_string)
	{
		m_secs ms = timer.elapsed();

		if (input_string->size() > 0 && ms > BACKSPACE_WAIT_TIME && ms > backspace_wait)
		{
			if (m_mod_flags & MOD_CTRL) // If Control is pressed, delete characters until ' ' is reached.
			{
				backspace_wait = ms + BACKSPACE_WORD_DELETE_TIME; // increase wait time so word deletion isnt too fast
				while (input_string->size() > 0)
				{
					input_string->pop_back();
					if (input_string->empty()) return;
					else if (input_string->back() == ' ') return;
				}
			}
			else // Delete by character, or if deleting by words, delete last space.
			{
				input_string->pop_back();
				backspace_wait = ms + BACKSPACE_CHAR_DELETE_TIME;
			}
		}
	}
}

void InputHandler::handleTextInput(const ALLEGRO_EVENT &ev)
{
	if (input_string != nullptr)
	{
		bool shift = (m_mod_flags & MOD_SHIFT) && INPUT_ALLOW_CAPS; // get if shift pressed
		unsigned char c = ev.keyboard.keycode;

		if (c <= ALLEGRO_KEY_Z)
		{
			c = letters[c];

			if (char(shift) & m_input_flags) c = toupper(c);

			stringPushBack(c);
		}
		else if (c <= ALLEGRO_KEY_PAD_9)
		{
			if (c <= ALLEGRO_KEY_9 && shift && INPUT_ALLOW_SPECIALS & m_input_flags)
			{
				c += 10; // if shift, increase number row to special characters
				stringPushBack(letters[c]);
			}
			else if (c >= ALLEGRO_KEY_PAD_0 && INPUT_ALLOW_NUMBERS & m_input_flags)
			{
				c -= 10; // If key pad is used, shrink to number row
				stringPushBack(letters[c]);
			}
			else if (INPUT_ALLOW_NUMBERS & m_input_flags)
			{
				stringPushBack(letters[c]);
			}
		}
		else
		{
			switch (c)
			{
			case ALLEGRO_KEY_FULLSTOP:
				if (INPUT_ALLOW_SPECIALS & m_input_flags) stringPushBack('.');
				break;
			case ALLEGRO_KEY_SPACE:
				if (INPUT_ALLOW_SPACE & m_input_flags) stringPushBack(' ');
				break;
			case ALLEGRO_KEY_ENTER:
				if (INPUT_ALLOW_NEWLINE & m_input_flags) stringPushBack('\n');
				break;
			case ALLEGRO_KEY_COMMA:
				if (INPUT_ALLOW_SPECIALS & m_input_flags) stringPushBack(',');
				break;
			default:
				break;
			}
		}
	}
}

void InputHandler::setInputString(std::string &in_string, unsigned short max_length, short flags)
{
	m_input_flags = flags;
	input_string = &in_string;
	max_input_length = max_length;
}

void InputHandler::clearInputString(void)
{
	*input_string = "";
}

void InputHandler::stopInputString()
{
	max_input_length = 0;
	input_string = nullptr;
}

bool InputHandler::isKeyPressed(const int key, const char &mod) const
{
	if (al_key_down(&cur_key_state, key) && !al_key_down(&prev_key_state, key))
	{
		if (mod == MOD_IGNORE || mod == m_mod_flags) return true;
	}

	return false;
}
bool InputHandler::isKeyReleased(const int key, const char &mod) const
{
	if (al_key_down(&prev_key_state, key) && !al_key_down(&cur_key_state, key))
	{
		if (mod == MOD_IGNORE || mod == m_mod_flags) return true;
	}

	return false;
}
bool InputHandler::isKeyDown(const int key, const char &mod) const
{
	if (al_key_down(&cur_key_state, key))
	{
		if (mod == MOD_IGNORE || mod == m_mod_flags) return true;
	}

	return false;
}

bool InputHandler::isMousePressed(const int button, const char &mod) const
{
	if (al_mouse_button_down(&cur_mouse_state, button) && !al_mouse_button_down(&prev_mouse_state, button))
	{
		if (mod == MOD_IGNORE || mod == m_mod_flags) return true;
	}

	return false;
}
bool InputHandler::isMouseReleased(const int button, const char &mod) const
{
	if (al_mouse_button_down(&prev_mouse_state, button) && !al_mouse_button_down(&cur_mouse_state, button))
	{
		if (mod == MOD_IGNORE || mod == m_mod_flags) return true;
	}

	return false;
}
bool InputHandler::isMouseDown(const int button, const char &mod) const
{
	if (al_mouse_button_down(&cur_mouse_state, button))
	{
		if (mod == MOD_IGNORE || mod == m_mod_flags) return true;
	}

	return false;
}

bool InputHandler::isMouseWheelDown(const char &mod) const
{
	if (cur_mouse_state.z < prev_mouse_state.z && (mod == MOD_IGNORE || mod == m_mod_flags))
	{
		return true;
	}
	else return false;
}
bool InputHandler::isMouseWheelUp(const char &mod) const
{
	if (cur_mouse_state.z > prev_mouse_state.z && (mod == MOD_IGNORE || mod == m_mod_flags))
	{
		return true;
	}
	else return false;
}

int InputHandler::getMouseX(void) const
{
	return cur_mouse_state.x;
}
int InputHandler::getMouseY(void) const
{
	return cur_mouse_state.y;
}
bool InputHandler::isMouseInWindow(void) const
{
	return (cur_mouse_state.display == al_get_current_display());
}