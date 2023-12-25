#pragma once
#include "ECS/ColliderComponent.h"

class ColliderComponent;

class Collision {
	
public:
	static bool AABBx(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABBy(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABB(ColliderComponent& colA, ColliderComponent& colB);
};
