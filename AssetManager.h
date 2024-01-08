#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/EntityComponentSystem.h"
#include "ItemMap.h"
//#include "SDL_ttf.h"

class AssetManager {
	Manager* manager;
	map<string, SDL_Texture*>textures;
	//map<string, TTF_Font*> fonts;

public:
	AssetManager(Manager* man);
	~AssetManager();
	//game objects
	void createRock(Vector2D pos, string id);
	void createMeat(Vector2D pos, string id);
	void createMandR(ItemMap& harta, string fisier, int sizeX, int sizeY);
	//texture manager
	void AddTexture(string id, const char* path);
	SDL_Texture* GetTexture(string id);

	//void AddFont(string id, string path, int fontSize);
	//TTF_Font* GetFont(string id);
};