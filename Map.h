#pragma once
#include "Game.h"

class Map {
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][32];

public:
	Map();
	~Map(){}
	void LoadMap(int arr[20][32]);
	void DrawMap();
};