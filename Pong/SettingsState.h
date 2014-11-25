#pragma once
#include "GameState.h"
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class SettingsState : public GameState
{
	enum Option { BALL_SPEED, POINTS, MODE };
	struct OptionEntry
	{
		Option option;
		SDL_Texture *name;
		SDL_Texture *optionTexture;
		std::vector<std::string> options;
		//index of a currently shown option
		int currentOption;
	};
	std::vector<OptionEntry> optionEntries;
	//index of an entry that is currently highlighted
	int currentOptionEntry;

	SDL_Color *textColor = &(SDL_Color{ 255, 255, 255, 255 });
	SDL_Color *backgroundColor = &(SDL_Color{ 0, 0, 0, 255 });

	SDL_Texture *title;
	TTF_Font *font;

	//@param up true for up, false for down
	void changeEntry(SDL_Renderer *renderer, bool up);
	//Creates OptionEntry object representing specified setting
	void addEntry(Option option, char* name, std::vector<std::string> options, SDL_Renderer *renderer, 
		bool chosen = false);
	/**
		Handles setting change (requested by left/right keyboard input)
		@direction 0 left(decrease); 1 right(increase)
	*/
	void changeOption(int direction, SDL_Renderer *renderer);
	//Looks up what the current setting is and returns corresponding OptionEntry.options index
	int SettingsState::loadSetting(Option option);
	
public:
	SettingsState(Game *game);
	virtual ~SettingsState();

	virtual void update(Game *game) {};
	virtual void render(Game *game);
	virtual void handleEvents(Game *game);
};