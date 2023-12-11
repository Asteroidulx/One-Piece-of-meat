#pragma once
#include "Game.h"

class GameObject {
	int xpos;
	int ypos;
public:
	GameObject(const char* texturesheet, SDL_Renderer* ren);
	~GameObject();
};