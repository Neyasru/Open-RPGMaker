#include <iostream>
#include <time.h> 

#include "GameScene.h"
#include "Engine.h"
#include "ECS/Components.h"

using namespace std;

GameScene::GameScene(Engine* engine) : Scene(engine) {
	srand((unsigned long)time(NULL));
	this->input = &(engine->input);

	entityManager = new EntityManager();
}

void GameScene::restart(void) {
	currentTime = 0.0f;
	fade = 1.0f;

	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	loadScript(L, "assets/scripts/player.lua");

	loadLuaFunctions(L);
	loadGetKeysFunction(L);

	player = &(entityManager->addEntity(L, "player"));
	player->addGroup(groupPlayers);

	luabridge::LuaRef loadAnimations = getGlobal(L, "loadAnimations");
	loadAnimations(LuaEntityHandle(player));


	loadScript(L, "assets/scripts/map.lua");
	loadGetKeysFunction(L);
	auto m = &(entityManager->addEntity(L, "map"));
	m->get<MapComponent>()->LoadMap();
	m->addGroup(groupMap);

	//lua_close(L);
}

void GameScene::update(void) {
	int w, h;
	SDL_GetWindowSize(Engine::instance().getWindow(), &w, &h);
	Engine::instance().camera.x = static_cast<int>(player->get<TransformComponent>()->position.x*player->get<TransformComponent>()->width*0.5 - w/2 + player->get<TransformComponent>()->width/2);
	Engine::instance().camera.y = static_cast<int>(player->get<TransformComponent>()->position.y*player->get<TransformComponent>()->heigth*0.5 - h/2 + player->get<TransformComponent>()->heigth/2);
	entityManager->update();
	
	if (Engine::instance().input.getPressedKey('l')) {
		cout << "Camara x:" << Engine::instance().camera.x << " Camara y:" << Engine::instance().camera.y << endl;
		cout << "Player x:" << player->get<TransformComponent>()->position.x << " Player y:" << player->get<TransformComponent>()->position.y << endl;
	}
}

void GameScene::render(void)  {
	for (auto& t : entityManager->getGroup(groupMap))
	{
		t->draw();
	}

	for (auto& p : entityManager->getGroup(groupPlayers))
	{
		p->draw();
	}
}

GameScene::~GameScene() {

}