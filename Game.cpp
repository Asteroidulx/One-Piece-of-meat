#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());
SDL_Event Game::event;

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

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/Luffy.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f,300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/Dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned!\n");
}

void Game::handleEvents() {
	
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
	if (Collision::AABB(player.getComponent<ColliderComponent>().getcollider(),
		wall.getComponent<ColliderComponent>().getcollider())) {
		player.getComponent<TransformComponent>().setvelocity(player.getComponent<TransformComponent>().getvelocity()*-1);
		cout <<"Wall Hit!"<< endl;
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

SDL_Event Game::getevent() {
	return event;
}

void Game::setevent(SDL_Event e) {
	event = e;
}