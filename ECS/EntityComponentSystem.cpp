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

bool Entity::hasGroup(Group mGroup) {
	return groupBitSet[mGroup];
}

void Entity::addGroup(Group mGroup) {
	groupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) {
	groupBitSet[mGroup] = false;
}


void Manager::update() {
	for (auto& e : entities) e->update();
}

void Manager::draw() {
	for (auto& e : entities) e->draw();
}

void Manager::refresh() {
	for (auto i(0u); i < maxGroups; ++i) {
		auto& v(groupedEntities[i]);
		v.erase(
			remove_if(begin(v), end(v), [i](Entity* mEntity) {
				return !mEntity->isActive() || !mEntity->hasGroup(i);
				}), end(v)
					);
	}

	entities.erase(remove_if(begin(entities), end(entities),
		[](const unique_ptr<Entity>& mEntity) {
			return !mEntity->isActive();
		}),
		end(entities));
}

void Manager::AddToGroup(Entity* mEntity, Group mGroup) {
	groupedEntities[mGroup].emplace_back(mEntity);
}

vector<Entity*>& Manager::getGroup(Group mGroup) {
	return groupedEntities[mGroup];
}

int Manager::getNrInGroup(Group mGroup) {
	return groupedEntities[mGroup].size();
}

Entity& Manager::addEntity() {
	Entity* e = new Entity(*this);
	unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(move(uPtr));
	return *e;
}