#ifndef GAMEOBJECTFACTORY_H_
#define GAMEOBJECTFACTORY_H_

#include "LuaHelperFunctions.h"
#include "Entity.h"
#include "LuaHelperFunctions.h"
#include "Components\GraphicsComponent.h"
#include "Components\NpcComponent.h"

#include <string>
#include <iostream>

class GameObjectFactory {
public:
    //GameObject* createGameObject ();
	Entity* loadEntity(lua_State* L, const std::string& type){
		using namespace luabridge;
		auto e = new Entity();
		e->setType(type);
		auto v = luah::getTableKeys(L, type);
		LuaRef entityTable = getGlobal(L, type.c_str());
		for (auto& componentName : v) {
			if (componentName == "GraphicsComponent") {
				LuaRef gcTable = entityTable["GraphicsComponent"];
				addComponent<GraphicsComponent>(e,gcTable);
			} else if (componentName == "NpcComponent") {
				LuaRef npccTable = entityTable["NpcComponent"];
				addComponent<NpcComponent>(e,npccTable);
			}
			
			std::cout << "Added " << componentName << " to " << type << std::endl;
		}
		return e;
	}

private:
	template <typename T>
	void addComponent(Entity* e, luabridge::LuaRef& componentTable) {
		e->addComponent(std::type_index(typeid(T)), new T(componentTable));
	}
};

#endif
