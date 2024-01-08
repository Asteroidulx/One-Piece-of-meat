#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"

class Rock : public Component {
	Vector2D position;
	TransformComponent* transform;
	enum falldirection {
		notMoving,
		down,
		right,
		left,
	};
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	bool anim = false;
	int caz = notMoving;
	bool falling = false;

public:
	Rock() {
		position.Zero();
	}
	Rock(Vector2D pos){
		position = pos;
	}
	~Rock(){}
	void init()override {
		transform = &entity->getComponent<TransformComponent>();
		transform->setposition(position);
		transform->sets(6.25);
		transform->setsp(2);
		ZeroVel();
	}

	void ZeroVel() {
		transform->setvelocity({0,0});
	}
	void update()override {
		

		updatevel();
	}

	void updatevel(){
		switch (caz) {
		case notMoving:
			anim = false;
			transform->vsetx(0);
			transform->vsety(0);
			spriteFlip = SDL_FLIP_NONE;
			falling = false;
			break;
		case down:
			anim = false;
			transform->vsetx(0);
			transform->vsety(1);
			spriteFlip = SDL_FLIP_NONE;
			falling = true;
			break;
		case right:
			anim = true;
			transform->vsetx(1);
			transform->vsety(0);
			spriteFlip = SDL_FLIP_NONE;
			falling = false;
			break;
		case left:
			anim = true;
			transform->vsetx(-1);
			transform->vsety(0);
			spriteFlip = SDL_FLIP_HORIZONTAL;
			falling = false;
			break;
		}
	}
	
	SDL_RendererFlip getFlip() {
		return spriteFlip;
	}

	bool getAnimation() {
		return anim;
	}
	Vector2D getVelocity() {
		return transform->getvelocity();
	}
	Vector2D getPosition() {
		return transform->getposition();
	}
	void setPosition(Vector2D pos) {
		return transform->setposition(pos);
	}
	void setVelocity(Vector2D vel) {
		return transform->setvelocity(vel);
	}
	bool getFalling() {
		return falling;
	}
	void setcase(int val) {
		caz = val;
	}
	int getcase() {
		return caz;
	}
	TransformComponent* getTrComp() {
		return transform;
	}
};
