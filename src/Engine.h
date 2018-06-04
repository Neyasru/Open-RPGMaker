#pragma once

#include <stdlib.h>
#include <vector>
#ifdef __MINGW32__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else 
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "InputManager.h"

class AssetsManager;
class ColliderComponent;
// Engine is a singleton (a class with a single instance) that represents our whole application

class Engine {

public:
	static Engine& instance() {
		static Engine engine;
		return engine;
	}

	void init(const char* title, int width, int height);
	void handleEvents();
	bool update();
	void render();
	void clean();

	void changeScene(Scene::scenes newScene);
	void finish();
	bool isFinished();
	SDL_Window* getWindow();
	
	InputManager input;
	AssetsManager* assets;
	SDL_Rect camera;
	SDL_Renderer *renderer;
	SDL_Event event;

	std::vector<ColliderComponent*> colliders;
	std::vector<ColliderComponent*> colliderscheckers;
private:
	bool finished;
	
	SDL_Window *window;
	
	Scene* scene;
	MenuScene* menuScene;
	GameScene* gameScene;
};