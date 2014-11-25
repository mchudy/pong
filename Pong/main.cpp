/**
PONG

Clone of the classic game written in SDL 2.0

@author Marcin Chudy
@version 1.0
@date 15-03-2014
*/
#include <stdio.h>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();
	if (!game)
	{
		printf("Game initialization error");
		return 1;
	}
	while (game->isRunning())
	{
		game->update();
		game->handleEvents();
		game->render();
	}
	delete game;
	return 0;
}