#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
auto& player(manager.addEntity());

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			printf("Renderer created!\n");
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	map = new Map();

	player.addComponent<TransformComponent>(0,64);
	player.addComponent<SpriteComponent>("assets/Luffy.png");
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
	manager.refresh();
	manager.update();

	player.getComponent<TransformComponent>().setposition(player.getComponent<TransformComponent>().getposition().Add(Vector2D(1,1)));
	if (player.getComponent<TransformComponent>().getx() > 100) {
		player.getComponent<SpriteComponent>().setTex("assets/Fridge.png");
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	//add stuff to render
	map->DrawMap();

	manager.draw();
	//until here
	SDL_RenderPresent(renderer);
}

bool Game::running() {
	return isRunning;
}

SDL_Renderer* Game::getrenderer() {
	return renderer;
}