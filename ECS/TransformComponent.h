#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
	Vector2D position;
	Vector2D velocity;
	int speed = 3;
	int height = 400;
	int width = 400;
	float scale = 7.5;
	int xposmov = 0; 
	int yposmov = 0;
	bool movfiny = true;
	bool movfinx = true;

public:
	TransformComponent() {
		position.Zero();
	}
	TransformComponent(int x, int y) {
		position.setx(x);
		position.sety(y);
	}
	TransformComponent(float s) {
		position.Zero();
		scale = s;
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
		else
			updatex();

		if (vgety() > 0)
			yposmov = 1;
		else if (vgety() < 0)
			yposmov = -1;
		else
			updatey();


		if(movfiny)
			psetx(pgetx() + vgetx() * speed);
		if(movfinx)
			psety(pgety() + vgety() * speed);
		
	}

	void updatex() {
		int interposx = pgetx() + 59;
		int leap = interposx % 64;
		if (leap) {
			movfinx = false;
			if (xposmov == 1) { //daca dupa deplasare entitatea nu se afla pe mijlocul casutei (5/64,5/64) 
				if (!((pgetx() + 60) % 64))
					psetx(pgetx() + 1);
				else
					if (!((pgetx() + 61) % 64))
						psetx(pgetx() + 2);
					else
						if ((pgetx() + 59) % 64)//x+1, x+2, x aliniat la 5px de multiplu de 64px
							psetx(pgetx() + speed);
			}
			else if (xposmov == -1) {
				if (!((pgetx() + 58) % 64))
					psetx(pgetx() - 1);
				else
					if (!((pgetx() + 57) % 64))
						psetx(pgetx() - 2);
					else
						if ((pgetx() + 59) % 64)//x-1, x-2, x aliniat la 5px de multiplu de 64px
							psetx(pgetx() - speed);
			}
		}
		else
			movfinx = true;
	}
	
	void updatey() {
		int interposy = pgety() + 59;
		int leap = interposy % 64;
		if (leap) {
			movfiny = false;
			if (yposmov == 1) { //daca dupa deplasare entitatea nu se afla pe mijlocul casutei (5/64,5/64) 
				if (!((pgety() + 60) % 64))
					psety(pgety() + 1);
				else
					if (!((pgety() + 61) % 64))
						psety(pgety() + 2);
					else
						if ((pgety() + 59) % 64)
							psety(pgety() + speed);
			}
			else if (yposmov == -1) {
				if (!((pgety() + 58) % 64))
					psety(pgety() - 1);
				else
					if (!((pgety() + 57) % 64))
						psety(pgety() - 2);
					else
						if ((pgety() + 59) % 64)
							psety(pgety() - speed);
			}
		}
		else
			movfiny = true;
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