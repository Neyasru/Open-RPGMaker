#include "Engine.h"

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	
	Uint32 frameStart;
	int frameTime;

	Engine::instance().init("ScriptRPG", 800, 600);
	
	while (!Engine::instance().isFinished())
	{
		frameStart = SDL_GetTicks();

		Engine::instance().handleEvents();
		Engine::instance().update();
		Engine::instance().render();

		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	Engine::instance().clean();
	return 0;
}


