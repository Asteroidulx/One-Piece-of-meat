#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
using namespace std;

#define MAX_WIDTH 1024
#define MAX_HEIGHT 640
typedef Uint32 atom;

class Game {
	bool isRunning;
	SDL_Window* window;
	static SDL_Renderer* renderer;
	
public:
	Game(const char* title, atom x, atom y, atom w, atom h, bool fullscreen);
	~Game();
	void handleEvents();
	void update();
	void render();
	bool running();

	static SDL_Renderer* getrenderer();
};