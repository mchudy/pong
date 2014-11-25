#include <sstream>
#include "GameOverState.h"
#include "Game.h"

GameOverState::GameOverState(Game *game, int win) : winner(win)
{
	std::ostringstream os;
	os << "Player " << winner << " won!";
	std::string strWinner = os.str();
	font = TTF_OpenFont("font.ttf", 80);
	winnerText = getTextTexture(game->getRenderer(), const_cast<char*>(strWinner.c_str()), font);
	TTF_CloseFont(font);
	font = TTF_OpenFont("font.ttf", 30);
	toDoText = getTextTexture(game->getRenderer(), "Press ENTER to play again\nPress ESC to go back to the menu", font,
		&(SDL_Color{ 255, 255, 255, 255 }), nullptr, 700);
}


GameOverState::~GameOverState()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(winnerText);
	SDL_DestroyTexture(toDoText);
}

void GameOverState::render(Game *game)
{
	SDL_Renderer *renderer = game->getRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, winnerText, nullptr, &(SDL_Rect{ 100, 100, 600, 100 }));
	SDL_RenderCopy(renderer, toDoText, nullptr, &(SDL_Rect{ 100, 360, 630, 70 }));
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void GameOverState::handleEvents(Game *game)
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
				game->changeState(Game::MAIN_MENU);
				break;
			case SDLK_RETURN:
				game->changeState(Game::MULTIPLAYER);
				break;
			}
			break;
		}
	}
}