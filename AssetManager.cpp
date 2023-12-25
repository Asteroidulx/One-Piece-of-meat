#include "AssetManager.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::AddTexture(string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(string id) {
	return textures[id];
}

//void AssetManager::AddFont(string id, string path, int fontSize) {
//	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
//}
//
//TTF_Font* AssetManager::GetFont(string id) {
//	return fonts[id];
//}