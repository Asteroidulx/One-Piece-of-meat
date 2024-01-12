#pragma once
using namespace std;
#include <string>

class ItemMap {
	int x, y;
	int** Map;

public:
	ItemMap(int _x, int _y): x(_x), y(_y) {
		Map = new int* [x];
		for (int i = 0; i < x; i++)
			Map[i] = new int[y];
		for (int i = 0; i < x; i++)
			for(int j = 0; j < y; j++)
				Map[i][j] = 0;
	}

	~ItemMap() {
		for (int i = 0; i < x; i++)
			delete[] Map[i];
		delete[] Map;
	}

	void AddtoMap(string id, int posX, int posY) {
		if (id == "nic") {
			Map[posX][posY] = 0;
		}
		else if (id == "meat") {
			Map[posX][posY] = 3;
		}
		else if (id == "rock") {
			Map[posX][posY] = 2;
		}
		else if (id == "wall") {
			Map[posX][posY] = 1;
		}
		else if (id == "nothing") {
			Map[posX][posY] = 9;
		}
	}

	int WhatatPos(Vector2D vec, int pos) { // 0->7 : patratele din jurul poz actuale 0 = deasupra, 1 = colt drt sus, ...
		int nrx, nry;
		switch (pos) {
		case 0: nrx = 0, nry = -1;
			break;
		case 1: nrx = 1, nry = -1;
			break;
		case 2: nrx = 1, nry = 0;
			break;
		case 3: nrx = 1, nry = 1;
			break;
		case 4: nrx = 0, nry = 1;
			break;
		case 5: nrx = -1, nry = 1;
			break;
		case 6: nrx = -1, nry = 0;
			break;
		case 7: nrx = -1, nry = -1;
			break;
		default: nrx = 0, nry = 0;
			break;
		}
		int x_ = static_cast<int>(vec.getx() / 64) + nrx;
		int y_ = static_cast<int>(vec.gety() / 64) + nry;
		if (x_ < 0 || x_ >= x || y_ < 0 || y_ >= y) {
			return 0;
		}
		else
			return Map[x_][y_];
	}

	void MeatDestroy(Vector2D pos) {
		Map[pos.getx()/64][pos.gety()/64] = 0;
	}

	void UpdatePos(Vector2D oldpos, Vector2D newpos) {
		if (gotoutofmap(newpos))
			Map[oldpos.getx() / 64][oldpos.gety() / 64] = 0;
		else {
			Map[static_cast<int>(oldpos.getx() / 64)][static_cast<int>(oldpos.gety() / 64)] = 0;
			Map[static_cast<int>(newpos.getx() / 64)][static_cast<int>(newpos.gety() / 64)] = 2;
		}
	}

	bool gotoutofmap(Vector2D pos) {
		if (pos.getx() < 0 || pos.getx() / 64 >= x-1 || pos.gety() < 0 || pos.gety() / 64 >= y-1)
			return true;
		else
			return false;
	}
};