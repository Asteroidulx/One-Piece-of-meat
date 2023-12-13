#include "Game.h"

int main(int argc, char* args[])
{
	const atom FPS = 60;
	const atom frameDelay = 1000 / FPS;

	atom frameStart;
	atom frameTime;

	Game *game = nullptr;

	game=new Game("One Piece of Meat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAX_WIDTH, MAX_HEIGHT, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->~Game();
	return 0;
}