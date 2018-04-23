#include <iostream>

#include "Scene.h"
#include "Engine.h"

using namespace std;

Scene::Scene(Engine* engine) {
	this->engine = engine;
}

Scene::~Scene() {

}
