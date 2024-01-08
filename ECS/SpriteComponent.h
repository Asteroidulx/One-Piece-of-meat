#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "../Game.h"
#include <map>
#include "../AssetManager.h"
#include "RockComponent.h"


class SpriteComponent : public Component {
	
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;
	int counter = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
	SpriteComponent() = default;
	SpriteComponent(string path) {
		setTex(path);
	}
	SpriteComponent(string id, int nrFrames, int mSpeed) {
		animated = true;
		frames = nrFrames;
		speed = mSpeed;
		setTex(id);
	}
	~SpriteComponent() {}

	void setTex(string id) {
		texture = Game::getassets()->GetTexture(id);
	}

	void init() override {
		if(entity->hasGroup(Game::groupRocks))
			transform = entity->getComponent<Rock>().getTrComp();
		else
			transform = &getEntity()->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->getw();
		srcRect.h = transform->geth();
	}
	void update() override {

		if (entity->hasGroup(Game::groupRocks)) {
			flip = entity->getComponent<Rock>().getFlip();
			if (entity->getComponent<Rock>().getAnimation()) {
				srcRect.x = srcRect.w * ((static_cast<int>(SDL_GetTicks() / speed)) % 10);
				srcRect.y = srcRect.h * ((static_cast<int>(SDL_GetTicks() / (10 * speed))) % 5);
				if ((srcRect.x == 9 * srcRect.w || srcRect.x == 8 * srcRect.w) && srcRect.y == 4 * srcRect.h)
					srcRect.x = srcRect.y = 0;
			}
			transform->setvelocity(entity->getComponent<Rock>().getVelocity());
			transform->setposition(entity->getComponent<Rock>().getPosition());
		}
		else {
			if (animated) {
				//player animation
			}
		}
		destRect.x = transform->pgetx() - Game::camera.x;
		destRect.y = transform->pgety() - Game::camera.y;
		destRect.w = transform->getw() / transform->gets();
		destRect.h = transform->geth() / transform->gets();
		
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, flip);
	}
};