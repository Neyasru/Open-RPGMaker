#include <iostream>
#include <time.h> 

#include "MenuScene.h"
#include "Engine.h"

using namespace std;

MenuScene::MenuScene(Engine* engine) :Scene(engine) {
	this->input = &(engine->input);
}

void MenuScene::restart(void) {

}

void MenuScene::update() {

}

void MenuScene::render(void) {

}

MenuScene::~MenuScene() {

}
