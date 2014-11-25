#pragma once
#include <SDL.h>
#include "GameState.h"

class Game
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	//flag that states if the program should be exited
	bool running;
	GameState *currentState;
public:
	enum GameStates { EXIT_STATE, MAIN_MENU, SETTINGS_MENU, MULTIPLAYER, GAME_OVER };
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	//informs whether the game is running, if not the program should be closed
	bool isRunning(){ return running; }
	void changeState(GameStates state, int winner = 0);
	SDL_Renderer* getRenderer() { return renderer; }
	GameState* getCurrentState(){ return currentState; }
	void handleEvents();
	void update();
	void render();
	Game();
	~Game();
};

