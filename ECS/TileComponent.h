#pragma once
#include "Components.h"
#include "SDL.h"

class TileComponent : public Component {
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
public:
	TileComponent() = default;
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcx, int srcy, int xpos, int ypos,int tsize, int tscale, string id){
		texture = Game::getassets()->GetTexture(id);

		position.setx(xpos);
		position.sety(ypos);

		srcRect.x = srcx;
		srcRect.y = srcy;
		srcRect.h = srcRect.w = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize*tscale;
	}

	void update() override {
		destRect.x = position.getx() - Game::camera.x;
		destRect.y = position.gety() - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};
