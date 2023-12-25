#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* mapa;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 1024, 640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

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

	/*if (TTF_Init() == -1) {
		cout << "Error : SDL_TTF" << endl;
	}*/
	
	assets->AddTexture("terrain", "assets/Lvl1MapTileset.png");
	assets->AddTexture("player", "assets/Luffy.png");

	//assets->AddFont("arial", "assets/arial.ttf", 16);

	mapa = new Map("terrain", 1, 64);
	mapa->LoadMap("assets/Lvl1Map.map", 32, 20);

	player.addComponent<TransformComponent>(133, 133);//(5, 1157);//(64*0+5, 64*18+5)
	player.addComponent<SpriteComponent>("player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	
	//SDL_Color white = { 255, 255, 255, 255 };
	//label.addComponent<UILabel>(10,10, "Test String", "arial", white);
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

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::update() {
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().getcollider();
	Vector2D playerPos = player.getComponent<TransformComponent>().getposition();

	/*stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");*/

	manager.refresh();
	manager.update();
	
	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().getcollider();
		if (Collision::AABBx(player.getComponent<ColliderComponent>().getcollider(), cCol) && player.getComponent<TransformComponent>().pgetx()!=playerPos.getx()) {
			player.getComponent<TransformComponent>().setposition(playerPos);
		}
		if (Collision::AABBy(player.getComponent<ColliderComponent>().getcollider(), cCol) && player.getComponent<TransformComponent>().pgety() != playerPos.gety()) {
			player.getComponent<TransformComponent>().setposition(playerPos);
		}
	}
	
	camera.x = player.getComponent<TransformComponent>().pgetx() - 480;
	camera.y = player.getComponent<TransformComponent>().pgety() - 288;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::render() {
	SDL_RenderClear(renderer);
	//add stuff to render
	for (auto& t : tiles) {
		t->draw();
	}

	/*for (auto& c : colliders) {
		c->draw();
	}*/

	for (auto& p : players) {
		p->draw();
	}

	//label.draw();

	//until here
	SDL_RenderPresent(renderer);
}

bool Game::running() {
	return isRunning;
}

void Game::setisrunning(bool cond) {
	isRunning = cond;
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

AssetManager* Game::getassets() {
	return assets;
}