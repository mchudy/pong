#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <cmath>
#include "Ball.h"
#include "Game.h"

const std::string Ball::imgFilePath = "ball.png";
int Ball::SPEED = 8;

Ball::Ball(SDL_Renderer *renderer)
{
	SDL_Surface *sur;
	sur = IMG_Load(imgFilePath.c_str());
	if (sur != nullptr)
	{
		img = SDL_CreateTextureFromSurface(renderer, sur);
		SDL_FreeSurface(sur);
	}
	else
		printf("Couldn't load the image: %s", SDL_GetError());
	srand(unsigned(time(nullptr)));
	start();
}

void Ball::start()
{
	x = Game::SCREEN_WIDTH / 2;
	y = rand() % Game::SCREEN_HEIGHT;
	velX = rand() % (SPEED - 3) + 3;
	velY = SPEED - velX;
	if (rand() % 2)
		velX = -velX;
	if (rand() % 2)
		velY = -velY;
	//printf("%2d %2d %d\n", velX, velY, abs(velX+velY));
	position = { x, y, BALL_SIZE, BALL_SIZE };
}

Ball::~Ball()
{
	SDL_DestroyTexture(img);
}

void Ball::move()
{
	position.x += velX;
	position.y += velY;
	//check for collision with boundaries
	if (position.y >= Game::SCREEN_HEIGHT || position.y <= 0)
		velY = -velY;
	//for debugging purposes
	//printf("%d %d\n", position.x, position.y);
	//printf("\nvelY: %d velx: %d\n", velY, velX);
}

//side 1 for player1 (left) 2 for player2 (right)
void Ball::checkPaddleCollision(const SDL_Rect &paddlePosition, Side side)
{
	if (position.y  <= (paddlePosition.y + paddlePosition.h) &&
		position.y + position.w * 0.5 >= (paddlePosition.y))
	{
		if ((side == LEFT && velX < 0 && position.x <= paddlePosition.x) || 
			(side == RIGHT && velX > 0 && position.x >= paddlePosition.x - paddlePosition.w))
				velX = -velX;
	}

}

Ball::Side Ball::checkWallCollision()
{
	if (position.x + position.w <= 0) return LEFT;
	if (position.x >= Game::SCREEN_WIDTH) return RIGHT;
	else return NONE;
}