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
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		transform = &getEntity()->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->getw();
		srcRect.h = transform->geth();
	}
	void update() override {
		destRect.x = static_cast<int>(transform->pgetx());
		destRect.y = static_cast<int>(transform->pgety());
		destRect.w = transform->getw() / transform->gets();
		destRect.h = transform->geth() / transform->gets();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};