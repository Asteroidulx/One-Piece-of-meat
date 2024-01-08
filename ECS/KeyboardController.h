#pragma once
#include "../Game.h"
#include "Components.h"

class KeyboardController : public Component {

public:
	TransformComponent* transform;
	void init()override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		if (Game::getevent().type == SDL_KEYDOWN) {
			switch (Game::getevent().key.keysym.sym) {
			case SDLK_w:
				transform->vsetx(0);
				transform->vsety(-1);
				transform->setmovoy(true);
				break;
			case SDLK_a:
				transform->vsety(0);
				transform->vsetx(-1);
				transform->setmovxo(true);
				break;
			case SDLK_s:
				transform->vsetx(0);
				transform->vsety(1);
				transform->setmovyo(true);
				break;
			case SDLK_d:
				transform->vsety(0);
				transform->vsetx(1);
				transform->setmovox(true);
				break;
			default:
				break;
			}
		}

		if (Game::getevent().type == SDL_KEYUP) {
			switch (Game::getevent().key.keysym.sym) {
			case SDLK_w:
				transform->vsety(0);
				if (transform->getmovox())
					transform->vsetx(1);
				if (transform->getmovxo())
					transform->vsetx(-1);
				transform->setmovoy(false);
				break;
			case SDLK_a:
				transform->vsetx(0);
				if (transform->getmovoy())
					transform->vsety(-1);
				if (transform->getmovyo())
					transform->vsety(1);
				transform->setmovxo(false);
				break;
			case SDLK_s:
				transform->vsety(0);
				if (transform->getmovox())
					transform->vsetx(1);
				if (transform->getmovxo())
					transform->vsetx(-1);
				transform->setmovyo(false);
				break;
			case SDLK_d:
				transform->vsetx(0);
				if (transform->getmovoy())
					transform->vsety(-1);
				if (transform->getmovyo())
					transform->vsety(1);
				transform->setmovox(false);
				break;
			case SDLK_ESCAPE:
				Game::setisrunning(false);
				break;
			default:
				break;
			}
		}
	}
};
