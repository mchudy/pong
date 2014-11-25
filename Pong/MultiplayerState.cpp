#include "MultiplayerState.h"
#include <SDL_image.h>
#include "Game.h"
#include <sstream>

int MultiplayerState::MAX_POINTS = 10;

MultiplayerState::MultiplayerState(Game *game)
{
	player1 = new Paddle(Paddle::LEFT);
	player2 = new Paddle(Paddle::RIGHT);
	ball = new Ball(game->getRenderer());
	SDL_Surface *sur = IMG_Load("net.png");
	if (!sur)
	{
		printf("Couldn't load the image: %s", SDL_GetError());
	}
	netImg = SDL_CreateTextureFromSurface(game->getRenderer(), sur);
	SDL_FreeSurface(sur);
	netPosition = { Game::SCREEN_WIDTH / 2 - 10, 0, 20, Game::SCREEN_HEIGHT };
	player1Score = 0;
	player2Score = 0;
	font = TTF_OpenFont("font.ttf", 70);
	updateScore(game->getRenderer());
}

MultiplayerState::~MultiplayerState()
{
	delete player1;
	delete player2;
	delete ball;
	SDL_DestroyTexture(netImg);
	TTF_CloseFont(font);
}

void MultiplayerState::handleEvents(Game *game)
{
	//continous input
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_GetScancodeFromKey(SDLK_UP)])
	{
		player2->moveUp();
	}
	if (keystate[SDL_GetScancodeFromKey(SDLK_DOWN)])
	{
		player2->moveDown();
	}
	if (keystate[SDL_GetScancodeFromKey(SDLK_w)])
	{
		player1->moveUp();
	}
	if (keystate[SDL_GetScancodeFromKey(SDLK_s)])
	{
		player1->moveDown();
	}

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->changeState(Game::EXIT_STATE);
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
						game->changeState(Game::MAIN_MENU);
				}
				break;
		}
	}
}

void MultiplayerState::update(Game *game)
{
	ball->checkPaddleCollision((player1->getPosition()), Ball::LEFT);
	ball->checkPaddleCollision((player2->getPosition()), Ball::RIGHT);
	ball->move();
	Ball::Side result = ball->checkWallCollision();
	if (result)
	{
		if (result == Ball::RIGHT)
			player1Score++;
		else
			player2Score++;
		updateScore(game->getRenderer());
		ball->start();
		if (player1Score == MAX_POINTS)
		{
			game->changeState(Game::GAME_OVER, 1);
			return;
		}
		else if (player2Score == MAX_POINTS)
		{
			game->changeState(Game::GAME_OVER, 2);
			return;
		}
	}
}

void MultiplayerState::render(Game *game)
{
	SDL_Renderer *renderer = game->getRenderer();
	//background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//net
	SDL_RenderCopy(renderer, netImg, nullptr, &netPosition);
	//paddles
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &(player1->getPosition()));
	SDL_RenderFillRect(renderer, &(player2->getPosition()));
	//ball
	SDL_RenderCopy(renderer, ball->getImage(), nullptr, &(ball->getPosition()));
	//scores
	SDL_RenderCopy(renderer, score, nullptr, &(SDL_Rect{ 800 / 2 - 90, 5, 180, 60 }));
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void MultiplayerState::updateScore(SDL_Renderer *renderer)
{
	std::ostringstream oss;
	oss << player1Score << " " << player2Score;
	SDL_Surface *sur = TTF_RenderText_Blended(font, oss.str().c_str(), SDL_Color{ 255, 255, 255 });
	score = SDL_CreateTextureFromSurface(renderer, sur);
	SDL_FreeSurface(sur);
}