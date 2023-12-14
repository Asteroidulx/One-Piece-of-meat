#pragma once
#include "../Game.h"
#include "EntityComponentSystem.h"
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
				transform->vsety(-1);
				break;
			case SDLK_a:
				transform->vsetx(-1);
				break;
			case SDLK_s:
				transform->vsety(1);
				break;
			case SDLK_d:
				transform->vsetx(1);
				break;
			default:
				break;
			}
		}

		if (Game::getevent().type == SDL_KEYUP) {
			switch (Game::getevent().key.keysym.sym) {
			case SDLK_w:
				transform->vsety(0);
				break;
			case SDLK_a:
				transform->vsetx(0);
				break;
			case SDLK_s:
				transform->vsety(0);
				break;
			case SDLK_d:
				transform->vsetx(0);
				break;
			default:
				break;
			}
		}
	}
};
