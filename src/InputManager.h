#pragma once

#include "Vector2D.h"

#define ARROW_UP	1
#define ARROW_DOWN	2
#define ARROW_LEFT	3
#define ARROW_RIGHT 4

class InputManager {

private:
	bool keys[256];
	bool specialKeys[256]; // Store key states so that 
	bool prevKeys[256];
	bool prevSpecialKeys[256];
	bool mousePressed;
	Vector2D mousePos;
	
public:
	//Set
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	//Get
	bool getPressedKey(int key);
	bool getPressedSpecialKey(int key);
	bool getPressedKeyOnce(int key);
	bool getPressedSpecialKeyOnce(int key);
	bool isMousePressed();
	Vector2D getMousePosition();
};