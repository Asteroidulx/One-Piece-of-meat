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
	srcRect.h = 32;
	srcRect.w = 32;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h*2;
	destRect.w = srcRect.w*2;
}

void Object::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}