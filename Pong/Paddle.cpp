#include "Paddle.h"
#include "Game.h"

Paddle::Paddle(Paddle::side side)
{
	if (side == LEFT)
		position = { PADDLE_START_X, PADDLE_START_Y, PADDLE_WIDTH, PADDLE_HEIGHT };
	else
		position = { Game::SCREEN_WIDTH - 2*PADDLE_START_X, PADDLE_START_Y, PADDLE_WIDTH, PADDLE_HEIGHT };
}

void Paddle::moveUp()
{
	(position.y - speed <= 0) ? position.y = 0 : position.y -= speed;
}

void Paddle::moveDown()
{
	(position.y + speed >= Game::SCREEN_HEIGHT - PADDLE_HEIGHT) ? position.y = Game::SCREEN_HEIGHT - PADDLE_HEIGHT 
		: position.y += speed;
}