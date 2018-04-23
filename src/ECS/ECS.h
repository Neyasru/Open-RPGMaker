#ifndef _ECS_H_
#define _ECS_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <array>
#include <bitset>
#include <typeindex> 
#include <LuaBridge/LuaBridge.h>

#include "../LuaHelperFunctions.h"

class Component;
class Entity;
class EntityManager;
class LuaEntityHandle;

namespace luabridge {
	class LuaRef;
}

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getComponentID() {
static ComponentID lastID = 0;
return lastID++;
}

template <typename T> inline ComponentID getComponentID() noexcept {
static ComponentID typeID = getComponentID();
return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>; 
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component {
protected:
	Entity * e;
	std::string id;
public:

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
	//virtual void receive(string message) = 0;

	void setEntity(Entity* e) {
		this->e = e;
	}

	Entity* getEntity() {
		return e;
	}

	std::string getId() { return id; }
	void setId(std::string id) { this->id = id; }

	virtual ~Component() {}
};

class LuaEntityHandle {
public:
	LuaEntityHandle(Entity *e) {
		this->e = e;
	}

	// Lua bindings
	void setAnimation(const std::string& animationName, int index, int row, int col, int frames, int speed);
	//int getAnimationFrame();
private:
	Entity * e;
};

class Entity {
public:
	
	Entity(EntityManager& mManager) : manager(mManager) {
		luaEntHand = new LuaEntityHandle(this);
	}

	void addComponent(std::type_index type, Component* c) {
		c->setEntity(this);
		components[type] = c;
	}

	template <typename T>
	T* get() {
		auto it = components.find(std::type_index(typeid(T)));
		if (it != components.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}

	void init() {
		for (auto& c : components) {
			c.second->init();
		}
	}

	void update() {
		for (auto& c : components) {
			c.second->update();
		}
	}

	void draw() {
		for (auto& c : components) {
			c.second->draw();
		}
	}

	void setType(const std::string& type) {
		this->type = type;
	}

	std::string getType() const {
		return type;
	}

	~Entity() {

	}

	bool isActive() { return active; }
	void destroy() { active = false; }
	
private:
	EntityManager& manager;
	LuaEntityHandle* luaEntHand;
	bool active = true;
	int uniqueID;
	GroupBitset groupBitset;
	std::string type;
	std::map<std::type_index, Component*> components;
	//static const int MAX_COMPONENTS = 10;
	//vector<Component*> components_;
};


class EntityManager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

	template <typename T>
	void addComponent(Entity* e, luabridge::LuaRef& componentTable) {
		e->addComponent(std::type_index(typeid(T)), new T(componentTable));
	}

public:
	void update() {
		for (auto& e : entities) {
			e->update();
		}
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {

		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
			return !mEntity->isActive();
		}), std::end(entities));
	}

	Entity& addEntity(luabridge::lua_State* L, const std::string& type);
	
	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	/*
	std::unique_ptr<Entity> getEntity(const std::string& type) {
		for (auto& e : entities) {
			if (e->getType() == type) {
				return e;
			}
		}
		return NULL;
	}*/

};

#endif