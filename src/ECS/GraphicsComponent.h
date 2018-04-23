#ifndef _GRAPHICSCOMPONENT_H_
#define _GRAPHICSCOMPONENT_H_

#include <iostream>
#include <string>
#include <LuaBridge/LuaBridge.h>

#include "../AssetsManager.h"
#include "../Engine.h"
#include "ECS.h"
#include "Animation.h"
#include <map>

class GraphicsComponent : public Component{
private:
	TransformComponent * transform;
	std::string imageID;
	int rows = 1;
	int columns = 1;
	
	Texture *texture;
	SDL_Rect srcRect, destRect;
	int numAnims = 0;

	int frames = 1;
	int speed = 100;
	int rowS = 0;
	int colS = 0;
public:

	int animIndex = 0;
	std::map<std::string, Animation> animations;
	
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	
	GraphicsComponent(luabridge::LuaRef& componentTable) {
		using namespace luabridge;
		auto imageIDRef = componentTable["imageID"];
		auto rowsRef = componentTable["rows"];
		auto columnsRef = componentTable["columns"];

		if (imageIDRef.isString()) {
			imageID = imageIDRef.cast<std::string>();
		}
		else {
			std::cout << "Error, GraphicsComponent.imageID is not a string!" << std::endl;
		}
		
		if (rowsRef.isNumber()) {
			rows = rowsRef.cast<int>();
		}
		else {
			std::cout << "Error, GraphicsComponent.numAnim is not a number!" << std::endl;
		}

		if (columnsRef.isNumber()) {
			columns = columnsRef.cast<int>();
		}
		else {
			std::cout << "Error, GraphicsComponent.framesPerAnimationRef is not a number!" << std::endl;
		}
	}

	void setTex(std::string id)
	{
		texture = Engine::instance().assets->getTexture(imageID);
	}

	void setAnimation(std::string id, int index, int row, int column, int frames,int speed) {
		animations.emplace(id, Animation(index, row, column, frames, speed));
		numAnims++;
	}

	int getNumAnims() {
		return numAnims;
	}

	void init() override {
		transform = e->get<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->heigth;
		setTex(imageID);
	}
	
	void update() override {
		if (numAnims != 0)
		{
			srcRect.x = srcRect.w * (static_cast<int>((SDL_GetTicks() / speed) % frames) + colS);
		}
		srcRect.y = srcRect.h*rowS;
	
		destRect.x = static_cast<int>(transform->position.x*transform->width*0.5 - Engine::instance().camera.x);
		destRect.y = static_cast<int>(transform->position.y*transform->heigth*0.5 - Engine::instance().camera.y);
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->heigth*transform->scale;
	}

	void draw() override {
		SDL_RenderCopyEx(Engine::instance().renderer, texture->get(), &srcRect, &destRect, 0, NULL, spriteFlip);
	}

	void setImageID(const std::string& imageID){
		this->imageID = imageID;
	}
	
	std::string getImageID() const {
		return imageID;
	}

	void Play(std::string animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
		rowS = animations[animName].rowS;
		colS = animations[animName].columnS;
	}

	~GraphicsComponent() {}
};

#endif

