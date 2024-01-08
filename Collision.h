#pragma once
#include "ECS/ColliderComponent.h"

class ColliderComponent;

class Collision {
	
public:
	static bool AABBplayer(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABBxplayer(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABByplayer(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABBx(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABBy(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
};
