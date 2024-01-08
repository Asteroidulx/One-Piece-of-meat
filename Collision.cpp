#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABBplayer(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.x + A.w > B.x && B.x + B.w > A.x &&
		A.y + A.h > B.y && B.y + B.h > A.y) {
		return true;
	}
	else
		return false;
}

bool Collision::AABBxplayer(const SDL_Rect& A, const SDL_Rect& B) {
	if (AABBplayer(A, B))
		if (A.x + A.w > B.x && B.x + B.w > A.x)
			return true;
	return false;
}

bool Collision::AABByplayer(const SDL_Rect& A, const SDL_Rect& B) {
	if (AABBplayer(A, B))
		if (A.y + A.h > B.y && B.y + B.h > A.y)
			return true;
	return false;
}

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.x + A.w >= B.x && B.x + B.w >= A.x &&
		A.y + A.h >= B.y && B.y + B.h >= A.y) {
		return true;
	}
	else
		return false;
}

bool Collision::AABBx(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.y + A.h > B.y && B.y + B.h > A.y)
		if(A.x + A.w >= B.x && B.x + B.w >= A.x)
			return true;
	return false;
}

bool Collision::AABBy(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.x + A.w > B.x && B.x + B.w > A.x)
		if(A.y + A.h >= B.y && B.y + B.h >= A.y)
			return true;
	return false;
}
