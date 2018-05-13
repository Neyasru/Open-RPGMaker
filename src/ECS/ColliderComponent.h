#ifndef _COLLIDERCOMPONENT_H_
#define _COLLIDERCOMPONENT_H_

#include "ECS.h"

class ColliderComponent : public Component{
private:
	TransformComponent * transform;
	std::string type;
	SDL_Rect colliderRect;	
	
	
public:
	ColliderComponent(luabridge::LuaRef& ColliderTable) {
		using namespace luabridge;
		auto typeRef = ColliderTable["type"];
		auto rectRef = ColliderTable["rect"];
		
		if (typeRef.isString()) {
			type = typeRef.cast<std::string>();
		}
		else {
			std::cout << "Error, ColliderComponent.type is not a string!" << std::endl;
		}
	}

	~ColliderComponent() {}
	
	void init() override {
		transform = e->get<TransformComponent>();
	}
	
	void update() override {
		colliderRect.x  = transform->position.x;
		colliderRect.x  = transform->position.y;
	}

	void draw() override {
		
	}
	
	bool checkCollision(SDL_Rect a, SDL_Rect b){
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
		leftB = b.x;
		rightB = b.x + b.w;
		topB = b.y;
		bottomB = b.y + b.h;
		
		//If any of the sides from A are outside of B
		if( bottomA <= topB )
		{
			return false;
		}

		if( topA >= bottomB )
		{
			return false;
		}

		if( rightA <= leftB )
		{
			return false;
		}

		if( leftA >= rightB )
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}
	
	void setRect(float x, float y, float w, float h){
		colliderRect.x = x;
		colliderRect.y = y;
		colliderRect.w = w;
		colliderRect.h = h;
	}
	
	SDL_Rect getRect(){
		return colliderRect;
	}
	
	void setType(std::string type){
		this->type = type;
	}
	
	std::string getType(){
		return type;
	}
	
};

#endif