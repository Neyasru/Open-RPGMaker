#ifndef _SCENE_H_
#define _SCENE_H_

//Abstract class to implement the diferents scenes
class Engine;

class Scene {

public:
	enum scenes {
		MENU_SCENE,
		GAME_SCENE
	};

	// Constructor
	Scene(Engine* engine);

	// Commune functions in all the scenes
	virtual void restart(void) = 0;
	virtual void render(void) = 0;
	virtual void update(void) = 0;
	
	// Destructor
	virtual ~Scene();

protected:
	Engine* engine;
};

#endif

