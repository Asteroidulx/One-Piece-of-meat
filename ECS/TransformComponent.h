#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
	Vector2D position;

public:
	TransformComponent() { position.setx(0.0f); position.sety(0.0f);  }
	TransformComponent(float x, float y) { position.setx(x); position.sety(y);}
	float getx(){return position.getx();}
	float gety() { return position.gety(); }
	void setx(float x) { position.setx(x); }
	void sety(float y){ position.setx(y); }
	void update() override { /*position.setx(position.getx() + 1); position.sety(position.gety() + 1); */ }
	void setposition(Vector2D v) { position.setx(v.getx());  position.sety(v.gety()); }
	Vector2D getposition() { return position; }
};