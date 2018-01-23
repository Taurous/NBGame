#pragma once

#include <string>
#include <bitset>
#include <allegro5/allegro.h>

#include "Util\Timer.h" //For timing character deletion
#include "Util\Logger.h"

//
//
//
//
//
// Stopped while trying to figure out how bitfields work, trying to get rid of my version of bit fields changed header, have not changed source.
//
//
//
//
//

namespace axe
{
	// Mouse key must be bit field, Allegro limitation
	const int MOUSE_LEFT	= 0b0001;
	const int MOUST_RIGHT	= 0b0010;
	const int MOUSE_MIDDLE	= 0b0100;

	const std::bitset<4> MOD_IGNORE		= 0b0000; // Ignores modifiers that are pressed (Allowing any modifier to be pressed)
	const std::bitset<4> MOD_NONE		= 0b0001; // Requires that no modifiers be pressed
	const std::bitset<4> MOD_SHIFT		= 0b0010;
	const std::bitset<4> MOD_CTRL		= 0b0100;
	const std::bitset<4> MOD_ALT		= 0b1000;

	const std::bitset<5> INPUT_ALLOW_CAPS		= 0b00000001;
	const std::bitset<5> INPUT_ALLOW_NEWLINE	= 0b00000010;
	const std::bitset<5> INPUT_ALLOW_NUMBERS	= 0b00000100;
	const std::bitset<5> INPUT_ALLOW_SPECIALS	= 0b00001000;
	const std::bitset<5> INPUT_ALLOW_SPACE		= 0b00010000;

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void getInput(const ALLEGRO_EVENT &ev);
		void setInputString(std::string &in_string, unsigned short max_length, const std::bitset<5> &flags);
		void clearInputString();
		void stopInputString();

		bool isKeyPressed(const int key, const std::bitset<4> &mod = MOD_IGNORE) const;
		bool isKeyReleased(const int key, const std::bitset<4> &mod = MOD_IGNORE) const;
		bool isKeyDown(const int key, const std::bitset<4> &mod = MOD_IGNORE) const;

		bool isMousePressed(const int button, const std::bitset<4> &mod = MOD_IGNORE) const;
		bool isMouseReleased(const int button, const std::bitset<4> &mod = MOD_IGNORE) const;
		bool isMouseDown(const int button, const std::bitset<4> &mod = MOD_IGNORE) const;
		bool isMouseWheelDown(const std::bitset<4> &mod = MOD_IGNORE) const;
		bool isMouseWheelUp(const std::bitset<4> &mod = MOD_IGNORE) const;

		int getMouseX() const;
		int getMouseY() const;
		bool isMouseInWindow() const;

	private:
		void handleTextInput(const ALLEGRO_EVENT &ev);
		void stringPushBack(char c);

		bool backspace;

		std::bitset<4> m_mod_flags;
		std::bitset<5> m_input_flags;

		unsigned short max_input_length;
		
		std::string *input_string;
	
		m_secs backspace_wait;
		Timer timer;

		ALLEGRO_KEYBOARD_STATE prev_key_state;
		ALLEGRO_KEYBOARD_STATE cur_key_state;

		ALLEGRO_MOUSE_STATE prev_mouse_state;
		ALLEGRO_MOUSE_STATE cur_mouse_state;

	};

};