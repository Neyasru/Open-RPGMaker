#include <cstdarg>
#include "Components.h"

void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

Entity& EntityManager::addEntity(luabridge::lua_State* L, const std::string& type) {
	using namespace luabridge;
	Entity* e = new Entity(*this);

	e->setType(type);
	auto v = getTableKeys(L, type);
	luabridge::LuaRef entityTable = getGlobal(L, type.c_str());
	for (auto& componentName : v) {
		if (componentName == "GraphicsComponent") {
			luabridge::LuaRef gcTable = entityTable["GraphicsComponent"];
			addComponent<GraphicsComponent>(e, gcTable);
		}
		else if (componentName == "NpcComponent") {
			luabridge::LuaRef npccTable = entityTable["NpcComponent"];
			addComponent<NpcComponent>(e, npccTable);
		}
		else if (componentName == "TransformComponent") {
			luabridge::LuaRef trfcTable = entityTable["TransformComponent"];
			addComponent<TransformComponent>(e, trfcTable);
		}
		else if (componentName == "InputComponent") {
			luabridge::LuaRef inputTable = entityTable["InputComponent"];
			addComponent<InputComponent>(e, inputTable);
		}
		else if (componentName == "EquipmentComponent") {
			luabridge::LuaRef equipTable = entityTable["EquipmentComponent"];
			addComponent<EquipmentComponent>(e, equipTable);
		}
		else if (componentName == "ColliderComponent") {
			luabridge::LuaRef colliderTable = entityTable["ColliderComponent"];
			addComponent<ColliderComponent>(e, colliderTable);
		}

		//std::cout << "Added " << componentName << " to " << type << std::endl;
	}

	e->init();

	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));

	return *e;
}

void LuaEntityHandle::setAnimation(const std::string& animationName, int index, int row, int col, int frames, int speed) {
	auto graphics = e->get<GraphicsComponent>();
	if (graphics) {
		graphics->setAnimation(animationName, index, row, col, frames, speed);
	}
	else {
		std::cout << "The entity does not have graphics component." << std::endl;
	}
}