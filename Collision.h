#pragma once
#include "ECS/ColliderComponent.h"

class Collision {
	
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
};
