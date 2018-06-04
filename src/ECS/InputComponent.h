#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include "ECS.h"
#include "../Engine.h"
#include "EquipmentComponent.h"
#define KEYPRESS(x) Engine::instance().input.getPressedKey(x)
#define KEYRELEASE(x) !Engine::instance().input.getPressedKey(x)

#define SKEYPRESS(x) Engine::instance().input.getPressedSpecialKey(x)
#define SKEYRELEASE(x) !Engine::instance().input.getPressedSpecialKey(x)

class InputComponent : public Component {
public:
	TransformComponent* transform;
	GraphicsComponent* graphics;
	EquipmentComponent* equip;
	ColliderComponent* collider;

	bool input; //1 = take input from keyboard/mouse,0 = demo/IA mode

	InputComponent(luabridge::LuaRef& componentTable) {
		using namespace luabridge;
		auto inputRef = componentTable["input"];

		if (inputRef.isNumber()) {
			input = (inputRef.cast<int>() != 0);
		}
		else {
			std::cout << "Error, InputComponent.playable is not a number!" << std::endl;
		}
	}

	void init() override {
		graphics = e->get<GraphicsComponent>();
		transform = e->get<TransformComponent>();
		equip = e->get<EquipmentComponent>();
		collider = e->get<ColliderComponent>();
	}

	void update() override {
		if (input) {
			if (KEYPRESS('w') || SKEYPRESS(ARROW_UP)) {
				transform->velocity.y = -1;
				graphics->Play("WALKING-REAR");
				if(equip != NULL) equip->Play("WALKING-REAR");
			}
			if (KEYPRESS('s') || SKEYPRESS(ARROW_DOWN)) {
				transform->velocity.y = 1;
				graphics->Play("WALKING-FRONT");
				if (equip != NULL) equip->Play("WALKING-FRONT");
			}
			if (KEYRELEASE('w') && KEYRELEASE('s') && SKEYRELEASE(ARROW_UP) && SKEYRELEASE(ARROW_DOWN)) {
				transform->velocity.y = 0;
			}

			if (KEYPRESS('a') || SKEYPRESS(ARROW_LEFT)) {
				transform->velocity.x = -1;
				graphics->Play("WALKING-LEFT");
				if (equip != NULL) equip->Play("WALKING-LEFT");
			}
			if (KEYPRESS('d') || SKEYPRESS(ARROW_RIGHT)) {
				transform->velocity.x = 1;
				graphics->Play("WALKING-RIGHT");
				if (equip != NULL) equip->Play("WALKING-RIGHT");
			}
			if (KEYRELEASE('a') && KEYRELEASE('d') && SKEYRELEASE(ARROW_LEFT) && SKEYRELEASE(ARROW_RIGHT)) {
				transform->velocity.x = 0;
			}

			if (KEYRELEASE('a') && KEYRELEASE('d') && KEYRELEASE('w') && KEYRELEASE('s') && 
				SKEYRELEASE(ARROW_UP) && SKEYRELEASE(ARROW_DOWN) && SKEYRELEASE(ARROW_LEFT) && SKEYRELEASE(ARROW_RIGHT)) {
				graphics->Play("IDLE-FRONT");
				if (equip != NULL) equip->Play("IDLE-FRONT");
			}

		}
		else {

		}
	}

	~InputComponent() {}
};

#endif