#include "Object.h"
#include "TextureManager.h"

Object::Object(const char* texturesheet, SDL_Renderer* ren, int x, int y) {
	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);
	xpos = x;
	ypos = y;
}

Object::~Object() {

}

void Object::Update() {
	xpos++;
	ypos++;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = 400;
	srcRect.w = 400;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w / 8;
	destRect.h = srcRect.h / 8;

	
}

void Object::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}