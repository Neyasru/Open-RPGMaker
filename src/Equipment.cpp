#include "Equipment.h"
#include "ECS/Components.h"

EquipmentManager::EquipmentManager(EntityManager *em) {
	entityManager = em; 
}

void EquipmentManager::loadEquipments(luabridge::lua_State* L){
		
	const std::string type = "equipments";
	auto v = getTableKeys(L, type);
	luabridge::LuaRef equipmentTable = getGlobal(L, type.c_str());
	for (auto& equipmentName : v) {
		Entity *aux_ent = &(entityManager->addEntity(L, equipmentName));

		luabridge::LuaRef loadAnimations = getGlobal(L, "loadAnimations");
		loadAnimations(LuaEntityHandle(aux_ent));

		equipments[equipmentName] = aux_ent;
	}
}

