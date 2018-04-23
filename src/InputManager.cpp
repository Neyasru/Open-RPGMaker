#include "InputManager.h"

void InputManager::keyPressed(int key)
{
	keys[key] = true;
}

void InputManager::keyReleased(int key)
{
	keys[key] = false;
	prevKeys[key] = false;
}

void InputManager::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void InputManager::specialKeyReleased(int key)
{
	specialKeys[key] = false;
	prevSpecialKeys[key] = false;
}

void InputManager::mouseMove(int x, int y)
{
	mousePos = Vector2D(x,y);
}

void InputManager::mousePress(int button)
{
	mousePressed = true;
}

void InputManager::mouseRelease(int button)
{
	mousePressed = false;
}

bool InputManager::getPressedKey(int key)
{
	prevKeys[key] = keys[key];
	return keys[key];
}

bool InputManager::getPressedSpecialKey(int key)
{
	prevSpecialKeys[key] = specialKeys[key];
	return specialKeys[key];
}

bool InputManager::getPressedKeyOnce(int key)
{
	if (!prevKeys[key] && keys[key]) {
		prevKeys[key] = keys[key];
		return true;
	}
	else {
		prevKeys[key] = keys[key];
		return false;
	}
}

bool InputManager::getPressedSpecialKeyOnce(int key)
{
	if (!prevSpecialKeys[key] && specialKeys[key]) {
		prevSpecialKeys[key] = specialKeys[key];
		return true;
	}
	else {
		prevSpecialKeys[key] = specialKeys[key];
		return false;
	}
}


bool InputManager::isMousePressed()
{
	return mousePressed;
}

Vector2D InputManager::getMousePosition()
{
	return mousePos;
}