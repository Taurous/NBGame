#include "Game.h"

int main(int argc, char ** argv)
{
	int msg;

	Game game;

	msg = game.init();

	if (msg)
	{
		game.destroy();
	}
	else
	{
		msg = game.run();
	}

	game.destroy();

	return msg;
}