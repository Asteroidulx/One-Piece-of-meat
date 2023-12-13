#include "Object.h"
#include "TextureManager.h"

Object::Object(const char* texturesheet, int x, int y) {
	objTexture = TextureManager::LoadTexture(texturesheet);
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
	destRect.w = 64;
	destRect.h = 64;
}

void Object::Render() {
	SDL_RenderCopy(Game::getrenderer(), objTexture, &srcRect, &destRect);
}
