#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
using namespace std;

#define MAX_WIDTH 1080
#define MAX_HEIGHT 600
typedef Uint32 atom;

class Game {
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
public:
	Game(const char* title, atom x, atom y, atom w, atom h, bool fullscreen);
	~Game();
	void handleEvents();
	void update();
	void render();
	bool running();
};