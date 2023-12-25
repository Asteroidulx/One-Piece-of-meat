#pragma once
using namespace std;
#include <string>

class Map {
	string texID;
	int mapScale;
	int tileSize;
	int scaledSize;

public:
	Map(string tID, int maps, int tscale);
	~Map();
	void LoadMap(string path, int sizeX, int sizeY);
	void AddTile(int srcx, int srcy, int xpos, int ypos);
};