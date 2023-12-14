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
	float scale = 6.25;

public:
	TransformComponent() { position.Zero();  }
	TransformComponent(float x, float y) { position.setx(x); position.sety(y);}
	TransformComponent(float s) { position.Zero(); scale = s; }
	TransformComponent(float x, float y, int h, int w,  float s) { position.setx(x); position.sety(y); height = h; width = w; scale = s; }

	void init()override {
		velocity.Zero();
	}
	void update() override {
		position.setx(position.getx() + velocity.getx() * speed);
		position.sety(position.gety() + velocity.gety() * speed);
	}

	int getw() { return width; }
	int geth() { return height; }
	void setw(int w) { width = w; }
	void seth(int h) { height = h; }
	float gets() { return scale; }
	void sets(float s) { scale = s; }
	float pgetx() { return position.getx(); }
	float pgety() { return position.gety(); }
	void psetx(float x) { position.setx(x); }
	void psety(float y) { position.sety(y); }
	float vgetx() { return velocity.getx(); }
	float vgety() { return velocity.gety(); }
	void vsetx(float x) { velocity.setx(x); }
	void vsety(float y) { velocity.sety(y); }
	void setposition(Vector2D v) { position.setx(v.getx());  position.sety(v.gety()); }
	Vector2D getposition() { return position; }
	void setvelocity(Vector2D v) { velocity.setx(v.getx());  velocity.sety(v.gety()); }
	Vector2D getvelocity() { return velocity; }
};