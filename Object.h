#pragma once
#include "Game.h"

class Object {
	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

public:
	Object(const char* texturesheet, int x, int y);
	~Object();
	void Update();
	void Render();
};