#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

//resolves the circular dependency problem
class Game;

//abstract class for representing game states
class GameState
{
protected:
	/**
	  Returns texture with the given text
	  If nullptr is passed as background uses TTF_RenderText_Blended_Wrapped, TTF_RenderText_Shaded otherwise
	*/
	SDL_Texture* getTextTexture(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color* color = &(SDL_Color{ 255, 255, 255, 255 }),
		SDL_Color* background = &(SDL_Color{ 0, 0, 0, 0 }), int wrap = 0);
public:
	virtual void handleEvents(Game *game) = 0;
	virtual void update(Game *game) = 0;
	virtual void render(Game *game) = 0;
};