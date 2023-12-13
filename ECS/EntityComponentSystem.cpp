#include "EntityComponentSystem.h"

void Entity::update() {
	for (auto& c : components) c->update();
}

void Entity::draw() {
	for (auto& c : components) c->draw();
}

bool Entity::isActive() const {
	return active;
}

void Entity::destroy() {
	active = false;
}


void Manager::update() {
	for (auto& e : entities) e->update();
}

void Manager::draw() {
	for (auto& e : entities) e->draw();
}

void Manager::refresh() {
	entities.erase(remove_if(begin(entities), end(entities),
		[](const unique_ptr<Entity>& mEntity) {
			return !mEntity->isActive();
		}),
		end(entities));
}

Entity& Manager::addEntity() {
	Entity* e = new Entity();
	unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(move(uPtr));
	return *e;
}