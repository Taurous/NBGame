#include "Game.h"

int main(int argc, char ** argv)
{
	if (!al_init())
	{
		return -1;
	}

	int msg;

	Game *game = new Game;

	msg = game->init();

	if (msg)
	{
		game->destroy();
	}
	else
	{
		msg = game->run();
	}

	game->destroy();

	delete game;

	return msg;
}