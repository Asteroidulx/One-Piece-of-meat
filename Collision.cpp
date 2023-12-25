#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.x+A.w+6>B.x && B.x+B.w+5>A.x &&
		A.y+A.h+6>B.y && B.y+B.h+5>A.y) {
		return true;
	}
	else
		return false;
}

bool Collision::AABBx(const SDL_Rect& A, const SDL_Rect& B) {
	if (AABB(A, B))
		if (A.x + A.w + 6 >= B.x && B.x + B.w + 5 >= A.x)
			return true;
	return false;
}

bool Collision::AABBy(const SDL_Rect& A, const SDL_Rect& B) {
	if (AABB(A, B))
		if (A.y + A.h + 6 >= B.y && B.y + B.h + 5 >= A.y)
			return true;
	return false;
}

bool Collision::AABB(ColliderComponent& colA, ColliderComponent& colB) {
	if (AABB(colA.getcollider(), colB.getcollider())) {
		//cout << colA.gettag() << " hit: " << colB.gettag() << endl;
		return true;
	}else
		return false;
}