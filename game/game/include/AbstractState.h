#pragma once

#include "axeEngine\DrawEngine.h"
#include "axeEngine\EventHandler.h"
#include "axeEngine\InputHandler.h"
#include <inttypes.h>

namespace axe
{
	class AbstractState
	{
	public:
		AbstractState() { }
		virtual ~AbstractState() { }

		virtual void init() = 0;
		virtual void cleanUp() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void handleEvents(InputHandler &input, EventHandler &events) = 0;
		virtual void update(InputHandler &input) = 0;
		virtual void draw(DrawEngine &draw) = 0;
	};
}