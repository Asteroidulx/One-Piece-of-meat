#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"
class TransformComponent : public Component
{
	Vector2D position;
	Vector2D velocity;
	int speed = 3;
	int height = 400;
	int width = 400;
	float scale = 6.25;
	int xposmov = 0; 
	int yposmov = 0;
	bool movfiny = true;
	bool movfinx = true;
	bool movox = false;//ex: sa pot face stg, sus, stg, fara sa apas din nou pe stg
	bool movoy = false;
	bool movxo = false;
	bool movyo = false;

public:
	TransformComponent() {
		position.Zero();
	}
	TransformComponent(int x, int y) {
		position.setx(x);
		position.sety(y);
	}
	
	TransformComponent(int x, int y, int h, int w, float s) {
		position.setx(x);
		position.sety(y);
		height = h;
		width = w;
		scale = s;
	}

	void init()override {
		velocity.Zero();
	}
	
	void update() override {
		if (vgetx() > 0)
			xposmov = 1;
		else if (vgetx() < 0)
			xposmov = -1;
		else if (speed == 3)
			update3x();
		else if (speed == 2)
			update2x();
		else if (speed == 1)
			update1x();

		if (vgety() > 0)
			yposmov = 1;
		else if (vgety() < 0)
			yposmov = -1;
		else if (speed == 3)
			update3y();
		else if (speed == 2)
			update2y();
		else if (speed == 1)
			update1y();

		if(movfiny)
			psetx(pgetx() + vgetx() * speed);
		if(movfinx)
			psety(pgety() + vgety() * speed);
	}

	void update1y() {
		int interposy = pgety();
		int leap = interposy % 64;
		if (leap) {
			movfiny = false;
			if (yposmov == 1) {
				if ((pgety()) % 64)
					psety(pgety() + speed);
			}
			else if (yposmov == -1) {
				if ((pgety()) % 64)
					psety(pgety() - speed);
			}
		}
		else
			movfiny = true;
	}
	void update1x() {
		int interposx = pgetx();
		int leap = interposx % 64;
		if (leap) {
			movfinx = false;
			if (xposmov == 1) {
				if ((pgetx()) % 64)
					psetx(pgetx() + speed);
			}
			else if (xposmov == -1) {
				if ((pgetx()) % 64)
					psetx(pgetx() - speed);
			}
		}
		else
			movfinx = true;
	}

	void update2y() {
		int interposy = pgety();
		int leap = interposy % 64;
		if (leap) {
			movfiny = false;
			if (yposmov == 1) { 
				if (!((pgety() + 1) % 64))
					psety(pgety() + 1);
				else
					if ((pgety()) % 64)
						psety(pgety() + speed);
			}
			else if (yposmov == -1) {
				if (!((pgety() + 63) % 64))
					psety(pgety() - 1);
				else
					if ((pgety()) % 64)
						psety(pgety() - speed);
			}
		}
		else
			movfiny = true;
	}
	void update2x() {
		int interposx = pgetx();
		int leap = interposx % 64;
		if (leap) {
			movfinx = false;
			if (xposmov == 1) { 
				if (!((pgetx() + 1) % 64))
					psetx(pgetx() + 1);
				else
					if ((pgetx()) % 64)
						psetx(pgetx() + speed);
			}
			else if (xposmov == -1) {
				if (!((pgetx() + 63) % 64))
					psetx(pgetx() - 1);
				else
					if ((pgetx()) % 64)
						psetx(pgetx() - speed);
			}
		}
		else
			movfinx = true;
	}

	void update3y() {
		int interposy = pgety();
		int leap = interposy % 64;
		if (leap) {
			movfiny = false;
			if (yposmov == 1) { 
				if (!((pgety() + 1) % 64))
					psety(pgety() + 1);
				else
					if (!((pgety() + 2) % 64))
						psety(pgety() + 2);
					else
						if ((pgety()) % 64)
							psety(pgety() + speed);
			}
			else if (yposmov == -1) {
				if (!((pgety() + 63) % 64))
					psety(pgety() - 1);
				else
					if (!((pgety() + 62) % 64))
						psety(pgety() - 2);
					else
						if ((pgety()) % 64)
							psety(pgety() - speed);
			}
		}
		else
			movfiny = true;
	}
	void update3x() {
		int interposx = pgetx();
		int leap = interposx % 64;
		if (leap) {
			movfinx = false;
			if (xposmov == 1) {  
				if (!((pgetx() + 1) % 64))
					psetx(pgetx() + 1);
				else
					if (!((pgetx() + 2) % 64))
						psetx(pgetx() + 2);
					else
						if ((pgetx()) % 64)
							psetx(pgetx() + speed);
			}
			else if (xposmov == -1) {
				if (!((pgetx() + 63) % 64))
					psetx(pgetx() - 1);
				else
					if (!((pgetx() + 62) % 64))
						psetx(pgetx() - 2);
					else
						if ((pgetx()) % 64)
							psetx(pgetx() - speed);
			}
		}
		else
			movfinx = true;
	}
	
	void setsp(int sp) {
		speed = sp;
	}
	int getsp() {
		return speed;
	}
	int getw() {
		return width;
	}
	int geth() {
		return height;
	}
	void setw(int w) {
		width = w;
	}
	void seth(int h) {
		height = h;
	}
	float gets() {
		return scale;
	}
	void sets(float s) {
		scale = s;
	}
	int pgetx() {
		return position.getx();
	}
	int pgety() {
		return position.gety();
	}
	void psetx(int x) {
		position.setx(x);
	}
	void psety(int y) {
		position.sety(y);
	}
	int vgetx() {
		return velocity.getx();
	}
	int vgety() {
		return velocity.gety();
	}
	bool getmovox() {
		return movox;
	}
	bool getmovoy() {
		return movoy;
	}
	void setmovox(bool mx) {
		movox = mx;
	}
	void setmovoy(bool my) {
		movoy = my;
	}
	bool getmovxo() {
		return movxo;
	}
	bool getmovyo() {
		return movyo;
	}
	void setmovxo(bool mx) {
		movxo = mx;
	}
	void setmovyo(bool my) {
		movyo = my;
	}
	void vsetx(int x) {
		velocity.setx(x);
	}
	void vsety(int y) {
		velocity.sety(y);
	}
	void setposition(Vector2D v) {
		position.setx(v.getx());
		position.sety(v.gety());
	}
	Vector2D getposition() {
		return position;
	}
	void setvelocity(Vector2D v) {
		velocity.setx(v.getx());
		velocity.sety(v.gety());
	}
	Vector2D getvelocity() {
		return velocity;
	}
};