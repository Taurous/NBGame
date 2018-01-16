#pragma once

#include "Util\Logger.h"

#include "DrawEngine.h"
#include "InputHandler.h"
#include "EventHandler.h"

#include "AbstractState.h"

#include <inttypes.h>
#include <vector>

/*
*	Note to self, need to remove the ability
*	to pop states until the list is empty.
*/


namespace axe
{
	enum
	{
		STATE_CHANGE,
		STATE_POP,
		STATE_PUSH
	};

	class StateManager
	{
	public:
		StateManager();
		~StateManager() { cleanUp(); }

		void init();
		void cleanUp();

		void changeState(AbstractState *state); // MUST CALL LAST
		void pushState(AbstractState *state);
		void popState();
		void popState(int _FLAG, AbstractState *st);

		void cleanStates();

		void handleEvents(InputHandler &input, EventHandler &events);
		void update(InputHandler &input);
		void draw(DrawEngine &draw);

		void setDrawAll(bool flag) { v_draw_all = flag; }

		bool running() { return v_running; }
		void quit() { v_running = false; }

	private:
		bool v_running;
		bool v_res;
		bool v_draw_all;

		std::vector<AbstractState*> states;
		std::vector<AbstractState*> deadStates;
	};

}