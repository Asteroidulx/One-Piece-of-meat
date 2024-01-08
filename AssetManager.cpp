#include "AssetManager.h"
#include "ECS/Components.h"
#include <fstream>

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

void AssetManager::createRock(Vector2D pos, string id) {
	auto& rock(manager->addEntity());
	rock.addComponent<TransformComponent>(pos.getx(), pos.gety());
	rock.addComponent<Rock>(pos);
	rock.addComponent<SpriteComponent>(id);
	rock.addComponent<ColliderComponent>("rock");
	rock.addGroup(Game::groupRocks);
}

void AssetManager::createMeat(Vector2D pos, string id) {
	auto& meat(manager->addEntity());
	meat.addComponent<TransformComponent>(pos.getx(), pos.gety());
	meat.addComponent<SpriteComponent>(id);
	meat.addComponent<ColliderComponent>("meat");
	meat.addGroup(Game::groupMeats);
}

void AssetManager::createMandR(ItemMap& harta, string fisier, int sizeX, int sizeY) {
	string n = "nothing", m = "meat", r = "rock", w = "wall";
	char c;
	fstream mapFile;
	mapFile.open(fisier);

	int src;
	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			mapFile.get(c);
			src = atoi(&c);
			if (src == 2) {
				harta.AddtoMap(r, x, y);
			}else if (src == 3){
				harta.AddtoMap(m, x, y);
			}else if (src == 0 && x==sizeX-1) {
				harta.AddtoMap(n, x, y);
			}else if (src == 1) {
				harta.AddtoMap(w, x, y);
			}	
			mapFile.ignore();
		}
	}
	mapFile.close();
	for (int y = sizeY; y >= 0; --y) {
		for (int x = 0; x < sizeX; ++x) {
			if (harta.WhatatPos({ x*64, y*64 }, 8) == 2)
				createRock({ x * 64, y * 64 }, r);
			else if(harta.WhatatPos({ x*64, y*64 }, 8) == 3)
				createMeat({ x * 64, y * 64 }, m);
		}
	}
}

//void AssetManager::AddFont(string id, string path, int fontSize) {
//	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
//}
//
//TTF_Font* AssetManager::GetFont(string id) {
//	return fonts[id];
//}