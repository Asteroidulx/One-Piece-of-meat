#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
	
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		transform = &getEntity()->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 400;
		destRect.w = destRect.h = 64;
	}
	void update() override {
		destRect.x = (int)transform->getx();
		destRect.y = (int)transform->gety();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};