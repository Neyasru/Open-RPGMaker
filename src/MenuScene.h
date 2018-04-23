#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_

#include "Scene.h"
#include "InputManager.h"

class Engine;

class MenuScene : public Scene {

public:
	// Constructor
	MenuScene(Engine* engine);
	// Destructor
	~MenuScene();

	void restart(void);
	void render(void);
	void update(void);

private:
	float currentTime;
	InputManager* input;
	
};


#endif