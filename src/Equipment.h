#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <LuaBridge/LuaBridge.h>
#include "LuaHelperFunctions.h"

class Entity;
class EntityManager;

class EquipmentManager {
private:
	EntityManager* entityManager;
	std::map<std::string, Entity*> equipments;

public:
	EquipmentManager(EntityManager *em);
	EntityManager* getEntityManager() {return entityManager;}
	void loadEquipments(luabridge::lua_State* L);
	Entity* getEquipment(std::string equipName){ return equipments[equipName];}
};

#endif
