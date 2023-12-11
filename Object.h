#pragma once
#include "Game.h"

class Object {
	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

public:
	Object(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~Object();
	void Update();
	void Render();
};