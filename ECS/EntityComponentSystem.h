#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using namespace std;

class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> 
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr size_t maxComponents = 32;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component {
public:Entity* entity;
	
public:
	virtual Entity* getEntity() { return this->entity; }
	virtual void setEntity(Entity* c) { this->entity = c; }
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component(){}
};

class Entity {
	bool active = true;
	vector<unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void update();
	void draw();
	bool isActive() const;
	void destroy();

	template <typename T>
	bool hasComponent()const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(forward<TArgs>(mArgs)...));
		c->setEntity(this);
		unique_ptr<Component> uPtr{ c };
		components.emplace_back(move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T>
	T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};


class Manager {
	vector<unique_ptr<Entity>>entities;

public:
	void update();
	void draw();
	void refresh();

	Entity& addEntity();
};

