#pragma once
#include <string.h>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
	SDL_Rect collider;
	string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;

public:
	ColliderComponent(string t) : tag(t) {}

	ColliderComponent(string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.w = collider.h = size;
	}

	void setcollider(SDL_Rect c) { collider = c; }
	SDL_Rect getcollider() { return collider; }
	string gettag() { return tag; }

	void init()override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/ColTex.png");
		srcR = {0, 0, 64, 64};
		destR = {collider.x, collider.y, collider.w, collider.h};
	}

	void update()override {
		if (tag != "terrain") {
			collider.x = transform->pgetx();
			collider.y = transform->pgety();
			collider.w = transform->getw() / transform->gets();
			collider.h = transform->geth() / transform->gets();
		}
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};