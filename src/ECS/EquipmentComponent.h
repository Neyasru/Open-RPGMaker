#ifndef _EQUIPMENTCOMPONENT_H_
#define _EQUIPMENTCOMPONENT_H_

#include <iostream>
#include <string>
#include <LuaBridge/LuaBridge.h>

#include "../AssetsManager.h"
#include "../Engine.h"
#include "ECS.h"
#include "../Equipment.h"
#include <map>

class EquipmentComponent : public Component{
private:
	EquipmentManager* equipManager;
	TransformComponent * transform;
	GraphicsComponent * graphics;
	std::string helmetID;
	std::string armorID;
	std::string legsID;
	std::string gloovesID;
	std::string shoesID;

	Entity* helmet;
	Entity* armor;
	Entity* legs;
	Entity* glooves;
	Entity* shoes;

public:

	EquipmentComponent(luabridge::LuaRef& componentTable) {
		using namespace luabridge;
		auto helmetRef = componentTable["helmet"];
		auto armorRef = componentTable["armor"];
		auto legsRef = componentTable["legs"];
		auto gloovesRef = componentTable["glooves"];
		auto shoesRef = componentTable["shoes"];

		if (helmetRef.isString()) {
			helmetID = helmetRef.cast<std::string>();
		}

		if (armorRef.isString()) {
			armorID = armorRef.cast<std::string>();
		}

		if (legsRef.isString()) {
			legsID = legsRef.cast<std::string>();
		}

		if (gloovesRef.isString()) {
			gloovesID = gloovesRef.cast<std::string>();
		}

		if (shoesRef.isString()) {
			shoesID = shoesRef.cast<std::string>();
		}
	}

	void setEquipmentManager(EquipmentManager* equipManager) {
		this->equipManager = equipManager;
		initEquip();
	}

	void initEquip() {
		transform = e->get<TransformComponent>();
		graphics = e->get<GraphicsComponent>();
		helmet = equipManager->getEquipment(helmetID);
		armor = equipManager->getEquipment(armorID);
		legs = equipManager->getEquipment(legsID);
		glooves = equipManager->getEquipment(gloovesID);
		shoes = equipManager->getEquipment(shoesID);
	}

	void setAnimation(std::string id, int index, int row, int column, int frames, int speed) {
		helmet->get<GraphicsComponent>()->setAnimation(id, index, row, column, frames, speed);
		armor->get<GraphicsComponent>()->setAnimation(id, index, row, column, frames, speed);
		legs->get<GraphicsComponent>()->setAnimation(id, index, row, column, frames, speed);
		glooves->get<GraphicsComponent>()->setAnimation(id, index, row, column, frames, speed);
		shoes->get<GraphicsComponent>()->setAnimation(id, index, row, column, frames, speed);
	}

	void init() override {

	}
	
	void update() override {
		if (helmet->get<TransformComponent>() != NULL) {
			helmet->get<TransformComponent>()->position = transform->position;
		}
		if (armor->get<TransformComponent>() != NULL) {
			armor->get<TransformComponent>()->position = transform->position;
		}
		if (legs->get<TransformComponent>() != NULL) {
			legs->get<TransformComponent>()->position = transform->position;
		}
		if (glooves->get<TransformComponent>() != NULL) {
			glooves->get<TransformComponent>()->position = transform->position;
		}
		if (shoes->get<TransformComponent>() != NULL) {
			shoes->get<TransformComponent>()->position = transform->position;
		}

	}

	void draw() override {
		if (helmet != nullptr) {
			helmet->get<TransformComponent>()->position = transform->position;
			helmet->draw();
		}
		if (armor != nullptr) {
			armor->get<TransformComponent>()->position = transform->position;
			armor->draw();
		}
		if (legs != nullptr) {
			legs->get<TransformComponent>()->position = transform->position;
			legs->draw();
		}
		if (glooves != nullptr) {
			glooves->get<TransformComponent>()->position = transform->position;
			glooves->draw();
		}
		if (shoes != nullptr) {
			shoes->get<TransformComponent>()->position = transform->position;
			shoes->draw();
		}
	}

	void Play(std::string animName)
	{
		helmet->get<GraphicsComponent>()->Play(animName);
		armor->get<GraphicsComponent>()->Play(animName);
		legs->get<GraphicsComponent>()->Play(animName);
		glooves->get<GraphicsComponent>()->Play(animName);
		shoes->get<GraphicsComponent>()->Play(animName);
	}
};

#endif

