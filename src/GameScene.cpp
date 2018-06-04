#include <iostream>
#include <time.h> 

#include "GameScene.h"
#include "Engine.h"
#include "Map.h"
#include "Equipment.h"
#include "ECS/Components.h"

using namespace std;

GameScene::GameScene(Engine* engine) : Scene(engine) {
	srand((unsigned long)time(NULL));
	this->input = &(engine->input);

	entityManager = new EntityManager();
	mapManager = new MapManager(entityManager);
	equipmentManager = new EquipmentManager(entityManager);

}

void GameScene::restart(void) {
	currentTime = 0.0f;
	fade = 1.0f;

	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	loadLuaFunctions(L);
	loadGetKeysFunction(L);
	
	if (loadScript(L, "assets/scripts/equipment.lua")) {
		equipmentManager->loadEquipments(L);
	}

	if(loadScript(L, "assets/scripts/player.lua")){
		player = &(entityManager->addEntity(L, "player"));
		
		luabridge::LuaRef loadAnimations = getGlobal(L, "loadAnimations");
		loadAnimations(LuaEntityHandle(player));
		player->get<EquipmentComponent>()->setEquipmentManager(equipmentManager);
		player->addGroup(groupPlayers);
	}
	
	if(loadScript(L, "assets/scripts/tiles.lua")){
		mapManager->loadTileReferences(L);
	}

	if(loadScript(L, "assets/maps/maps.lua")){
		mapManager->addMaps(L);
	}

/*
	loadScript(L, "assets/scripts/map.lua");
	loadGetKeysFunction(L);
	auto m = entityManager->addEntity(L, "map");
	m.get<MapComponent>()->LoadMap();*/


	//lua_close(L);
}

void GameScene::update(void) {
	int w, h;
	SDL_GetWindowSize(Engine::instance().getWindow(), &w, &h);
	Engine::instance().camera.x = static_cast<int>(player->get<TransformComponent>()->position.x*player->get<TransformComponent>()->width*player->get<TransformComponent>()->scale-w / 2 + player->get<TransformComponent>()->width / 2);
	Engine::instance().camera.y = static_cast<int>(player->get<TransformComponent>()->position.y*player->get<TransformComponent>()->heigth*player->get<TransformComponent>()->scale-h / 2 + player->get<TransformComponent>()->heigth / 2);
	
	int numColliders = Engine::instance().colliderscheckers.size();
	for(int i = 0; i < numColliders; i++) {
		int numTotalColliders = Engine::instance().colliders.size();
		ColliderComponent* checker = Engine::instance().colliderscheckers[i];
		for (int j = 0; j < numTotalColliders; j++) {
			ColliderComponent* checked = Engine::instance().colliders[j];
			if (checker != checked) {
				bool collision = checker->checkCollision(checker->getRect(),checked->getRect());
				if (collision && checker->getType() != "None" &&  checked->getType() != "None") {
					//std::cout << "Collision i:" << i << " j:" << j << std::endl;
					checker->collided();
					
				}
			}
		}
	}

	entityManager->update();
	
	if (Engine::instance().input.getPressedKey('l')) {
		cout << "Camara x:" << Engine::instance().camera.x << " Camara y:" << Engine::instance().camera.y << endl;
		cout << "Player x:" << player->get<TransformComponent>()->position.x << " Player y:" << player->get<TransformComponent>()->position.y << endl;
	}
}

void GameScene::render(void)  {
	mapManager->drawLayer(0);
	mapManager->drawLayer(1);
	for (auto& p : entityManager->getGroup(groupPlayers))
	{
		p->draw();
		if (p->get<EquipmentComponent>() != NULL) {
			p->get<EquipmentComponent>()->draw();
		}
	}


}

GameScene::~GameScene() {

}