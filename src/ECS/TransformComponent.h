#ifndef _POSCOMPONENT_H_
#define _POSCOMPONENT_H_

#include <string>
#include <iostream>
#include <LuaBridge/LuaBridge.h>
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component{
public:
	Vector2D position;
	Vector2D safe_position;
	Vector2D previous_position;
	Vector2D velocity;

	int heigth = 32;
	int width = 32;
	float scale = 1;

	float speed = 3;

	bool blocked = false;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(float sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		heigth = h;
		width = w;
		scale = sc;
	}

	TransformComponent(luabridge::LuaRef& PositionTable) {
		using namespace luabridge;
		auto xRef = PositionTable["x"];
		auto yRef = PositionTable["y"];
		auto scaleRef = PositionTable["scale"];
		auto wRef = PositionTable["w"];
		auto hRef = PositionTable["h"];
		auto speedRef = PositionTable["speed"];

		if (xRef.isNumber()) {
			position.x = xRef.cast<float>();
		}
		else {
			std::cout << "Error, TransformComponent.position.x is not a number" << std::endl;
		}

		if (yRef.isNumber()) {
			position.y = yRef.cast<float>();
		}
		else {
			std::cout << "Error, TransformComponent.position.y is not a number" << std::endl;
		}

		if (!scaleRef.isNil()) {
			if (scaleRef.isNumber()) {
				scale = scaleRef.cast<float>();
			}
			else {
				std::cout << "Error, TransformComponent.scale is not a number" << std::endl;
			}
		}

		if (!wRef.isNil()) {
			if (wRef.isNumber()) {
				width = wRef.cast<int>();
			}
			else {
				std::cout << "Error, TransformComponent.width is not a number" << std::endl;
			}
		}


		if (!hRef.isNil()) {
			if (hRef.isNumber()) {
				heigth = hRef.cast<int>();
			}
			else {
				std::cout << "Error, TransformComponent.height is not a number" << std::endl;
			}
		}

		if (!speedRef.isNil()) {
			if (speedRef.isNumber()) {
				speed = speedRef.cast<float>();
			}
			else {
				std::cout << "Error, TransformComponent.speed is not a number" << std::endl;
			}
		}

	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		safe_position = previous_position;
		previous_position = position;
		if (velocity.x != 0 && velocity.y == 0)
			position.x += static_cast<float>(velocity.x * speed);
		if (velocity.x == 0 && velocity.y != 0)
			position.y += static_cast<float>(velocity.y * speed);
		if (velocity.x != 0 && velocity.y != 0) {
			position.x += static_cast<float>(velocity.x * speed*0.707);
			position.y += static_cast<float>(velocity.y * speed*0.707);
		}
	}

	void collisionUpdate() {
		position = safe_position;
	}
	~TransformComponent() {}
};

#endif