#include "Game.h"
#include "TextureManager.h"
#include "Object.h"

Object* player;
Object* fridge;

Game::Game(const char* title, atom x, atom y, atom w, atom h, bool fullscreen) {
	atom flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("Subsystems Initialised!...\n");

		window=SDL_CreateWindow(title, x, y, w, h, flags);
		if (window) {
			printf("Window created!\n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 20, 205, 255, 255);
			printf("Renderer created!\n");
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	player = new Object("assets/Luffy.png", renderer, 0, 0);
	fridge = new Object("assets/Fridge.png", renderer, 50, 50);
}

Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned!\n");
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT: isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	player->Update();
	fridge->Update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//add stuff to render
	player->Render();
	fridge->Render();
	//until here
	SDL_RenderPresent(renderer);
}

bool Game::running() {
	return isRunning;
}