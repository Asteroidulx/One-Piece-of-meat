#include "Game.h"

int main(int argc, char* args[])
{
	const atom FPS = 60;
	const atom frameDelay = 1000 / FPS;

	atom frameStart;
	atom frameTime;

	Game *game = nullptr;
	SDL_Event event;
	game=new Game("One Piece of Meat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAX_WIDTH, MAX_HEIGHT, false);
	game->lvlinit(1);
	game->update();
	
	while (game->running()) {
		bool breakok1 = false;
		while (game->running()) {
			
			bool breakok = false;
			while(SDL_PollEvent(&event)){
				if(event.type ==SDL_KEYUP)
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:game->right--;
					breakok = true;
					break;
				case SDLK_RIGHT:game->right++;
					breakok = true;
					break;
				default: breakok = false;
					break;
				}
			}
			if (game->right == 11)
				breakok1 = true;
			if (game->right == -1) {
				breakok1 = true;
				game->setisrunning(false);
			}
			if (breakok)
				break;
			frameStart = SDL_GetTicks();
			game->handleEvents();
			//game->update();
			game->render();
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}
		if (breakok1)
			break;
	}
	game->right = -1;
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		
		if (game->getlevelclear()) {
			while (game->running()) {
				
				bool breakok = false;
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYUP)
						switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: game->setesc(true);
						breakok = true;
						break;
					case SDLK_RIGHT: game->setclevel(game->getclevel()+1);
						if(game->getclevel()<=3)game->lvlinit(game->getclevel());
						game->exitdead = false;
						breakok = true;
						break;
					default: breakok = false;
						break;
						}
				}
				if (breakok)
					break;
				frameStart = SDL_GetTicks();
				game->handleEvents();
				//game->update();
				game->render();
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}
			game->setlevelclear(false);
		}
		if (game->getclevel() == 4 && !game->exitlvl4) {
			while (game->running()) {

				bool breakok = false;
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYUP)
						switch (event.key.keysym.sym) {
						case SDLK_RIGHT: 
							breakok = true;
							break;
						default: breakok = false;
							break;
						}
				}
				if (breakok) {
					game->exitlvl4 = true;
					break;
				}
				frameStart = SDL_GetTicks();
				game->handleEvents();
				//game->update();
				game->render();
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}
		}

		if (game->playerdied && game->livesleft) {
			while (game->running()) {

				bool breakok = false;
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYUP)
						switch (event.key.keysym.sym) {
						case SDLK_RIGHT: game->lvlinit(game->getclevel());
							breakok = true;
							break;
						default: breakok = false;
							break;
						}
				}
				if (breakok) {
					game->playerdied = false;
					break;
				}
				frameStart = SDL_GetTicks();
				game->handleEvents();
				//game->update();
				game->render();
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}
		}

		if (!game->livesleft && !game->exitdead) {
			while (game->running()) {

				bool breakok = false;
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYUP)
						switch (event.key.keysym.sym) {
						case SDLK_RIGHT: 
							breakok = true;
							break;
						default: breakok = false;
							break;
						}
				}
				if (breakok) {
					game->exitdead = true;
					break;
				}
				frameStart = SDL_GetTicks();
				game->handleEvents();
				//game->update();
				game->render();
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}
		}

		if ((game->getclevel() == 4 && game->exitlvl4) || !game->livesleft) {
			while (game->running()) {

				bool breakok = false;
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYUP)
						switch (event.key.keysym.sym) {
						case SDLK_e: breakok = true;
							game->setisrunning(false);
							break;
						case SDLK_r: game->lvlinit(1);
							game->setmeat(0);
							game->setclevel(1);
							game->livesleft = 3;
							game->exitdead = false;
							breakok = true;
							break;
						default: breakok = false;
							break;
						}
				}
				if (breakok) {
					game->playerdied = false;
					break;
				}
				frameStart = SDL_GetTicks();
				game->handleEvents();
				//game->update();
				game->render();
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}
		}

		if (game->getesc()) {
			while (game->running()) {
				bool breakok = false;
				if (game->getevent().type == SDL_KEYUP)
					switch (game->getevent().key.keysym.sym) {
					case SDLK_t: breakok = true;
						break;
					case SDLK_l: game->lvlinit(game->getclevel());							
						game->livesleft--;
						breakok = true;
						break;
					case SDLK_e: breakok = true;
						game->setisrunning(false);
						break;	
					case SDLK_r: game->lvlinit(1);
						game->setclevel(1);
						game->setmeat(0);
						game->exitdead = false;
						game->livesleft = 3;
						breakok = true;
						break;
					default: breakok = false;
						break;
					}
				if (breakok)
					break;
				frameStart = SDL_GetTicks();
				game->handleEvents();
				//game->update();
				game->render();
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}
			game->setesc(false);
		}
	}
	game->~Game();
	return 0;
}