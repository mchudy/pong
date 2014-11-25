#pragma once
#include <SDL_ttf.h>
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Game.h"

class MultiplayerState : public GameState
{
	TTF_Font *font;
	Paddle *player1;
	Paddle *player2;
	Ball *ball;
	SDL_Rect netPosition;
	SDL_Texture *score;
	SDL_Texture *netImg;
	int player1Score;
	int player2Score;
	void updateScore(SDL_Renderer *);
	bool running;
public:
	MultiplayerState(Game *game);
	virtual ~MultiplayerState();

	static int MAX_POINTS;
	virtual void handleEvents(Game *game);
	virtual void update(Game *game);
	virtual void render(Game *game);
};