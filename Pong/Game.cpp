#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "MainMenuState.h"
#include "MultiplayerState.h"
#include "SettingsState.h"
#include "GameOverState.h"

Game::Game()
{
	running = false;
	SDL_Window* window = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
			if (renderer == nullptr)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			}
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			if (TTF_Init() == 0)
			{
				running = true;
				currentState = new MainMenuState(this);
			}
		}
	}
}

Game::~Game()
{
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::changeState(GameStates state, int winner)
{
	delete currentState;
	switch (state)
	{
		case EXIT_STATE:
			currentState = nullptr;
			running = false;
			break;
		case MAIN_MENU:
			currentState = new MainMenuState(this);
			break;
		case SETTINGS_MENU:
			currentState = new SettingsState(this);
			break;
		case MULTIPLAYER:
			currentState = new MultiplayerState(this);
			break;
		case GAME_OVER:
			currentState = new GameOverState(this, winner);
			break;
	}
}

void Game::handleEvents()
{
	if (currentState) currentState->handleEvents(this);
}

void Game::update()
{
	if (currentState) currentState->update(this);
}

void Game::render()
{
	if (currentState) currentState->render(this);
}
