#include <util\Logger.h>
#include "Game.h"

int main(int argc, char ** argv)
{
#ifndef _DEBUG
	axe::setOutputFile("log.txt");
#endif

	if (!al_init())
	{
		axe::crash("Unable to initialize Allegro!");
	}

	Game game;

	game.run();

	return EXIT_SUCCESS;
}