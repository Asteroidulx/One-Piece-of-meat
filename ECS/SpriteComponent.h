#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "../Game.h"
#include <map>
#include "../AssetManager.h"


class SpriteComponent : public Component {
	
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	//bool animated = false;
	//int frames = 0;
	//int speed = 100;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	SpriteComponent(string id, int nrFrames, int mSpeed) {
		//animated = true;
		//frames = nrFrames;
		//speed = mSpeed;
		setTex(id);
	}
	~SpriteComponent() {}

	void setTex(string id) {
		texture = Game::getassets()->GetTexture(id);
	}

	void init() override {
		transform = &getEntity()->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->getw();
		srcRect.h = transform->geth();
	}
	void update() override {

		/*if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}*/

		destRect.x = transform->pgetx() - Game::camera.x;
		destRect.y = transform->pgety() - Game::camera.y;
		destRect.w = transform->getw() / transform->gets();
		destRect.h = transform->geth() / transform->gets();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
};