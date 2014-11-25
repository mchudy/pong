#include "GameState.h"
#include <SDL.h>
#include <SDL_ttf.h>


SDL_Texture* GameState::getTextTexture(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color* color,
	SDL_Color* background, int wrap)
{
	SDL_Surface* sur = nullptr;
	SDL_Texture* texture = nullptr;
	if (!background)
	{
		sur = TTF_RenderText_Blended_Wrapped(font, text, *color, wrap);
	}
	else
	{
		sur = TTF_RenderText_Shaded(font, text, *color, *background);
	}
	SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0, 0, 0));
	texture = SDL_CreateTextureFromSurface(renderer, sur);
	SDL_FreeSurface(sur);
	return texture;
}