#pragma once

#include "Util\Timer.h"
#include "Util\Logger.h"
#include "Util\Util.h"

#include <string>
#include <allegro5/allegro.h>


namespace axe
{
	enum 
	{
		MOUSE_LEFT = 1,
		MOUSE_RIGHT = 2,
		MOUSE_MIDDLE = 4
	};
	enum
	{
		MOD_IGNORE	= 0b000'00000, //ignore modifiers
		MOD_NONE	= 0b000'00001, //requires no modifiers down
		MOD_SHIFT	= 0b000'00010,
		MOD_CTRL	= 0b000'00100,
		MOD_ALT		= 0b000'01000
	};
	enum
	{
		INPUT_ALLOW_CAPS		= 0b0000'0001,
		INPUT_ALLOW_NEWLINE		= 0b0000'0010,
		INPUT_ALLOW_NUMBERS		= 0b0000'0100,
		INPUT_ALLOW_SPECIALS	= 0b0000'1000,
		INPUT_ALLOW_SPACE		= 0b0001'0000
	};

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void init(void);

		void getInput(const ALLEGRO_EVENT &ev);
		void setInputString(std::string &in_string, unsigned short max_length, short flags = 0);
		void clearInputString();

		bool isKeyPressed(const int key, const char &mod = MOD_IGNORE) const;
		bool isKeyReleased(const int key, const char &mod = MOD_IGNORE) const;
		bool isKeyDown(const int key, const char &mod = MOD_IGNORE) const;

		bool isMousePressed(const int button, const char &mod = MOD_IGNORE) const;
		bool isMouseReleased(const int button, const char &mod = MOD_IGNORE) const;
		bool isMouseDown(const int button, const char &mod = MOD_IGNORE) const;
		bool isMouseWheelDown(const char &mod = MOD_IGNORE) const;
		bool isMouseWheelUp(const char &mod = MOD_IGNORE) const;

		int getMouseX() const;
		int getMouseY() const;
		bool isMouseInWindow() const;

	private:
		bool initialized;
		bool backspace;

		char m_mod_flags;
		char m_input_flags;

		unsigned short max_input_length;
		
		std::string *input_string;
	
		
		m_secs backspace_wait;
		Timer timer;

		ALLEGRO_KEYBOARD_STATE prev_key_state;
		ALLEGRO_KEYBOARD_STATE cur_key_state;

		ALLEGRO_MOUSE_STATE prev_mouse_state;
		ALLEGRO_MOUSE_STATE cur_mouse_state;

		void stringPushBack(char c);
	};

};