#pragma once
#include <SDL.h>

class Paddle
{
	SDL_Rect position;
	static const int PADDLE_START_X = 10;
	static const int PADDLE_START_Y = 260;
	static const int PADDLE_WIDTH = 12;
	static const int PADDLE_HEIGHT = 90;
	static const int speed = 8;
public:
	enum side {LEFT, RIGHT};
	void moveUp();
	void moveDown();
	const SDL_Rect& getPosition(){ return position; };
	Paddle(Paddle::side side);
};