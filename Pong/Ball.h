#pragma once
#include <SDL.h>
#include <string>

class Ball
{
	int x, y;
	int velX, velY;
	static const std::string imgFilePath;
	SDL_Texture *img;
	SDL_Rect position;
	//diameter
	static const int BALL_SIZE = 20;
public:
	static int SPEED;
	//for handling collisions with left or right boundaries
	enum Side { NONE, LEFT, RIGHT };
	void move();
	void checkPaddleCollision(const SDL_Rect &paddlePosition, Side side);
	Side checkWallCollision();
	SDL_Texture* getImage(){ return img; };
	const SDL_Rect& getPosition(){ return position; }
	/**
		Generates random starting point and velocity, as the constructor only loads an image
		and creates texture; this method is to be called whenever new round starts
	*/
	void start();
	Ball(SDL_Renderer *renderer);
	~Ball();
};