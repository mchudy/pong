#include "MainMenuState.h"
#include "MultiplayerState.h"
#include <SDL_ttf.h>


MainMenuState::MainMenuState(Game *game)
{
	font = TTF_OpenFont("font.ttf", 40);
	menu = getTextTexture(game->getRenderer(), "Press ENTER to play\nPress S to enter settings\nPress ESC to quit", 
		font, &(SDL_Color{ 255, 255, 255, 255 }), nullptr, 700);
	font = TTF_OpenFont("font.ttf", 300);
	title = getTextTexture(game->getRenderer(), "PONG", font);
}

MainMenuState::~MainMenuState()
{
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(menu);
	TTF_CloseFont(font);
}

void MainMenuState::render(Game *game)
{
	SDL_Renderer *renderer = game->getRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, title, nullptr, &(SDL_Rect{ 100, 100, 600, 200 }));
	SDL_RenderCopy(renderer, menu, nullptr, &(SDL_Rect{ 180, 380, 500, 100 }));
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void MainMenuState::handleEvents(Game *game)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			game->changeState(Game::EXIT_STATE);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					game->changeState(Game::EXIT_STATE);
					break;
				case SDLK_RETURN:
					game->changeState(Game::MULTIPLAYER);
					break;
				case SDLK_s:
					game->changeState(Game::SETTINGS_MENU);
					break;
			}
			break;
		}
	}
}