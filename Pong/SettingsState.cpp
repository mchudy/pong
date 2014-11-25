#include "SettingsState.h"
#include "MultiplayerState.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Ball.h"

SettingsState::SettingsState(Game *game)
{
	SDL_Renderer *renderer = game->getRenderer();
	font = TTF_OpenFont("font.ttf", 80);
	title = getTextTexture(renderer, "SETTINGS", font, textColor, nullptr);
	TTF_CloseFont(font);
	font = TTF_OpenFont("font.ttf", 50);
	currentOptionEntry = 0;
	addEntry(BALL_SPEED, "BALL SPEED", { "normal", "fast", "insane" }, renderer, true);
	addEntry(POINTS, "POINTS", { "  2  ","  3  ", "  4  ","  5  ", "  6  ","  7  ", "  8  ", "  9  ", "  10  " }, renderer);
}

SettingsState::~SettingsState()
{
	for (OptionEntry &oe : optionEntries)
	{
		SDL_DestroyTexture(oe.name);
		SDL_DestroyTexture(oe.optionTexture);
	}
	SDL_DestroyTexture(title);
	TTF_CloseFont(font);
}

void SettingsState::handleEvents(Game *game)
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
				case SDLK_DOWN:
					changeEntry(game->getRenderer(), false);
					break;
				case SDLK_UP:
					changeEntry(game->getRenderer(), true);
					break;
				case SDLK_LEFT:
					changeOption(0, game->getRenderer());
					break;
				case SDLK_RIGHT:
					changeOption(1, game->getRenderer());
					break;
			}
			break;
		}
	}
}

void SettingsState::render(Game *game)
{
	SDL_Renderer *renderer = game->getRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, title, nullptr, &(SDL_Rect{ 300, 30, 200, 80 }));
	for (int i = 0; i < optionEntries.size(); i++)
	{
		SDL_RenderCopy(renderer, optionEntries[i].name, nullptr, &(SDL_Rect{ 180, 140 + 60*i, 200, 40 }));
		SDL_RenderCopy(renderer, optionEntries[i].optionTexture, nullptr, &(SDL_Rect{ 430, 140 + 60*i, 200, 40 }));
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void SettingsState::changeEntry(SDL_Renderer *renderer, bool up)
{
	SDL_SetTextureColorMod(optionEntries[currentOptionEntry].optionTexture, 60, 60, 60);
	if (up)
	{
		currentOptionEntry--;
		if (currentOptionEntry < 0)
		{
			currentOptionEntry = optionEntries.size() - 1;
		}
	}
	else
	{
		currentOptionEntry++;
		if (currentOptionEntry > optionEntries.size() - 1)
		{
			currentOptionEntry = 0;
		}
	}
	SDL_SetTextureColorMod(optionEntries[currentOptionEntry].optionTexture, 100, 180, 130);
}

void SettingsState::addEntry(Option option, char* name, std::vector<std::string> options, SDL_Renderer *renderer, bool chosen)
{
	OptionEntry oe;
	oe.option = option;
	oe.name = getTextTexture(renderer, name, font, textColor, backgroundColor);
	oe.options = options;
	oe.currentOption = loadSetting(option);
	oe.optionTexture = getTextTexture(renderer, const_cast<char*>(options[oe.currentOption].c_str()), font, textColor,
		backgroundColor);
	if (chosen)
	{
		SDL_SetTextureColorMod(oe.optionTexture, 100, 180, 130);
	}
	else
	{
		SDL_SetTextureColorMod(oe.optionTexture, 60, 60, 60);
	}
	optionEntries.push_back(oe);
}

void SettingsState::changeOption(int direction, SDL_Renderer *renderer)
{
	int previousOption = optionEntries[currentOptionEntry].currentOption;
	if (direction)
	{
		if (optionEntries[currentOptionEntry].currentOption < optionEntries[currentOptionEntry].options.size() - 1)
		{
			optionEntries[currentOptionEntry].currentOption++;
		}
	}
	else if (optionEntries[currentOptionEntry].currentOption > 0)
	{
			optionEntries[currentOptionEntry].currentOption--;
	}
	//if the option has changed
	if (previousOption != optionEntries[currentOptionEntry].currentOption)
	{
		switch (optionEntries[currentOptionEntry].option)
		{
		case BALL_SPEED:
			switch (optionEntries[currentOptionEntry].currentOption)
			{
			case 0://NORMAL
				Ball::SPEED = 8;
				break;
			case 1: //FAST
				Ball::SPEED = 12;
				break;
			case 2: //INSANE
				Ball::SPEED = 18;
				break;
			}
			break;
		case POINTS:
			MultiplayerState::MAX_POINTS = optionEntries[currentOptionEntry].currentOption + 2;
			break;
		}
		//reload texture
		SDL_DestroyTexture(optionEntries[currentOptionEntry].optionTexture);
		optionEntries[currentOptionEntry].optionTexture = getTextTexture(renderer,
			const_cast<char*>(optionEntries[currentOptionEntry].options[optionEntries[currentOptionEntry].currentOption].c_str()),
			font, textColor, backgroundColor);
		SDL_SetTextureColorMod(optionEntries[currentOptionEntry].optionTexture, 100, 180, 130);
	}
}


int SettingsState::loadSetting(Option option)
{
	switch (option)
	{
	case BALL_SPEED:
		switch (Ball::SPEED)
		{
		case 8:
			return 0;
		case 12:
			return 1;
		case 18:
			return 2;
		default:
			return 0;
		}
		break;
	case POINTS:
		//min 2 points, indexing starts from 0
		return MultiplayerState::MAX_POINTS - 2;
		break;
	}
	return 0;
}