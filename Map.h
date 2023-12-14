#pragma once
#include "Game.h"

class Map {
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][32];//map[32][60]; //for screen resolution = 1920x1080 (fullscreen)

public:
	Map();
	~Map();
	void LoadMap(int arr[20][32]/*arr[32][60] */ );
	void DrawMap();
};