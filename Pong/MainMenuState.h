#pragma once
#include <SDL.h>
#include "GameState.h"
#include "Game.h"
#include <SDL_ttf.h>

class MainMenuState : public GameState
{
	TTF_Font *font;
	SDL_Texture *menu;
	SDL_Texture *title;
public:
	MainMenuState(Game *game);
	virtual void update(Game *game) {};
	virtual void render(Game *game);
	virtual void handleEvents(Game *game);
	virtual ~MainMenuState();
};

