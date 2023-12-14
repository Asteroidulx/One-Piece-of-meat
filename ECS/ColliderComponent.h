#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component {
	SDL_Rect collider;
	string tag;

	TransformComponent* transform;

public:
	ColliderComponent(string t) : tag(t) {}

	void setcollider(SDL_Rect c) { collider = c; }
	SDL_Rect getcollider() { return collider; }

	void init()override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update()override {
		collider.x = static_cast<int>(transform->pgetx());
		collider.y = static_cast<int>(transform->pgety());
		collider.w = transform->getw() / transform->gets();
		collider.h = transform->geth() / transform->gets();
	}
};