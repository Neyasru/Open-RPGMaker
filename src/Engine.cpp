#include <iostream>

#include "Engine.h"
#include "AssetsManager.h"

void Engine::init(const char* title, int width, int height)
{
	renderer = nullptr;
	camera = { 0,0,800,640 };
	int flags = 0;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
		}

		finished = false;
	}

/*	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}*/
	
	
	assets = new AssetsManager();
	menuScene = new MenuScene(this);
	gameScene = new GameScene(this);

	changeScene(Scene::GAME_SCENE);
}

void Engine::handleEvents()
{
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			finished = true;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym < 256)
				input.keyPressed(event.key.keysym.sym);
			else {
				switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					input.specialKeyPressed(ARROW_DOWN);
					break;
				case SDLK_UP:
					input.specialKeyPressed(ARROW_UP);
					break;
				case SDLK_RIGHT:
					input.specialKeyPressed(ARROW_RIGHT);
					break;
				case SDLK_LEFT:
					input.specialKeyPressed(ARROW_LEFT);
					break;
				}
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym < 256)
				input.keyReleased(event.key.keysym.sym);
			else {
				switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					input.specialKeyReleased(ARROW_DOWN);
					break;
				case SDLK_UP:
					input.specialKeyReleased(ARROW_UP);
					break;
				case SDLK_RIGHT:
					input.specialKeyReleased(ARROW_RIGHT);
					break;
				case SDLK_LEFT:
					input.specialKeyReleased(ARROW_LEFT);
					break;
				}
			}
			break;
		default:
			break;
		}
	}
}

bool Engine::update()
{
	scene->update();
	return finished;
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	scene->render();
	SDL_RenderPresent(renderer);
}

void Engine::changeScene(Scene::scenes newScene) {
	switch (newScene) {
	case Scene::MENU_SCENE:
		scene = menuScene;
		break;
	case Scene::GAME_SCENE:
		scene = gameScene;
		break;
	}

	scene->restart();
}

SDL_Window* Engine::getWindow() {
	return window;
}

void Engine::finish() {
	finished = true;
}

bool Engine::isFinished() {
	return finished;
}

void Engine::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}