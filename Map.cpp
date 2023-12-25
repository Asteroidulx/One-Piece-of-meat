#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/EntityComponentSystem.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(string tID, int maps, int tsize): texID(tID), mapScale(maps), tileSize(tsize) {
	scaledSize = maps * tsize;
}

Map::~Map() {
	
}

void Map::LoadMap(string path, int sizeX, int sizeY) {
	char c;
	fstream mapFile;
	mapFile.open(path);

	int srcx, srcy=0;

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			mapFile.get(c);
			srcx = atoi(&c) * tileSize;
			AddTile(srcx, srcy, x*scaledSize, y*scaledSize);
			mapFile.ignore();
		}
	}
	mapFile.ignore();
	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcx, int srcy, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcx, srcy, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}