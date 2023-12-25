#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
using namespace std;

#define MAX_WIDTH 1024//1920
#define MAX_HEIGHT 640//1080
typedef Uint32 atom;

class AssetManager;
class ColliderComponent;

class Game {
	static bool isRunning;
	SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Event event;	
	static AssetManager *assets;
public:
	enum groupLabels : size_t {
		groupMap,
		groupPlayers,
		groupColliders
	};

	Game(const char* title, atom x, atom y, atom w, atom h, bool fullscreen);
	~Game();
	void handleEvents();
	void update();
	void render();
	
	static SDL_Rect camera;
	static AssetManager* getassets();
	static void setisrunning(bool cond);
	static bool running();
	static SDL_Renderer* getrenderer();
	static SDL_Event getevent();
	static void setevent(SDL_Event);
};