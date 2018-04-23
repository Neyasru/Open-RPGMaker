#ifndef _TILECOMPONENT_H_
#define _TILECOMPONENT_H_

#include "ECS.h"
#include "../Vector2D.h"
#include "../Engine.h"
#include "../AssetsManager.h"

class TileComponent : public Component
{
public:
	Texture *texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	{
		texture = Engine::instance().assets->getTexture(id);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;
		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = static_cast<int>(position.x);
		destRect.y = static_cast<int>(position.y);
	}
	void draw() override
	{
		SDL_RenderCopyEx(Engine::instance().renderer, texture->get(), &srcRect, &destRect, 0, NULL, SDL_FLIP_NONE);
	}

	~TileComponent()
	{
	}
};

#endif