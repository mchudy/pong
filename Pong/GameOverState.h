#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
	TTF_Font *font;
	//Texture with text announcing the winner
	SDL_Texture *winnerText;
	//Texture with further options: play again or go back to menu
	SDL_Texture *toDoText;
	int winner;
public:
	GameOverState(Game *game, int win);
	virtual ~GameOverState();

	virtual void handleEvents(Game *game);
	virtual void update(Game *game) {};
	virtual void render(Game *game);
};

