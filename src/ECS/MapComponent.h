#ifndef _MAPCOMPONENT_H_
#define _MAPCOMPONENT_H_

#include <fstream>

#include "ECS.h"
#include "../Vector2D.h"
#include "../Engine.h"
#include "../AssetsManager.h"
#include <typeindex>

class MapComponent : public Component
{
private:
	std::string imageID;
	Texture *texture;
	SDL_Rect srcRect, destRect;
	std::string pathMap;
	vector< vector<int> > map;
	int sizeX = 1, sizeY = 1;
	int mapScale = 1, scaledSize, tileSize;
	int tileSetColumns, tileSetRows;
public:

	MapComponent(luabridge::LuaRef& componentTable)
	{
		int error = false;
		using namespace luabridge;
		auto imageIDRef = componentTable["imageID"];
		auto sizeXRef = componentTable["sizeX"];
		auto sizeYRef = componentTable["sizeY"];
		auto pathMapRef = componentTable["path"];
		auto tileSizeRef = componentTable["tileSize"];
		auto tileSetColumnsRef = componentTable["tileSetColumns"];
		auto tileSetRowsRef = componentTable["tileSetRows"];
		auto mapScaleRef = componentTable["mapScale"];

		if (imageIDRef.isString()) {
			imageID = imageIDRef.cast<std::string>();
		}
		else {
			std::cout << "Error, MapComponent.imageID is not a string!" << std::endl;
			error = true;
		}

		if (pathMapRef.isString()) {
			pathMap = pathMapRef.cast<std::string>();
		}
		else {
			std::cout << "Error, MapComponent.pathMap is not a string!" << std::endl;
			error = true;
		}

		if (tileSizeRef.isNumber()) {
			tileSize = tileSizeRef.cast<int>();
		}
		else {
			std::cout << "Error, MapComponent.tileSize is not a number!" << std::endl;
			error = true;
		}

		if (tileSetColumnsRef.isNumber()) {
			tileSetColumns = tileSetColumnsRef.cast<int>();
		}
		else {
			std::cout << "Error, MapComponent.tileSetColumns is not a number!" << std::endl;
			error = true;
		}

		if (tileSetRowsRef.isNumber()) {
			tileSetRows = tileSetRowsRef.cast<int>();
		}
		else {
			std::cout << "Error, MapComponent.tileSetRows is not a number!" << std::endl;
			error = true;
		}

		if (mapScaleRef.isNumber()) {
			mapScale = mapScaleRef.cast<int>();
		}
		else {
			std::cout << "Error, MapComponent.mapScale is not a number!" << std::endl;
			error = true;
		}

		if (sizeXRef.isNumber()) {
			sizeX = sizeXRef.cast<int>();
		}
		else {
			std::cout << "Error, MapComponent.sizeX is not a number!" << std::endl;
			error = true;
		}

		if (sizeYRef.isNumber()) {
			sizeY = sizeYRef.cast<int>();
		}
		else {
			std::cout << "Error, MapComponent.sizeY is not a number!" << std::endl;
			error = true;
		}
		map = vector<vector<int>>(sizeY, vector<int>(sizeX));
		texture = Engine::instance().assets->getTexture(imageID);
		srcRect.h = tileSize;
		srcRect.w = tileSize;
		destRect.h = tileSize * mapScale;
		destRect.w = tileSize * mapScale;
	}

	void LoadMap() {
		scaledSize = mapScale * tileSize;
		std::ifstream mapFile(pathMap);
		//mapFile.open(pathMap);

		int srcX, srcY;

		for (int y = 0; y < sizeY-1; y++)
		{
			for (int x = 0; x < sizeX-1; x++)
			{
				string input;
				getline(mapFile, input, ',');
				int val = stoi(input);
				map[y][x] = val;
				//srcX = val% tileSetSize;
				//srcY = val/ tileSetSize;
				//AddTile(srcX, srcY, x*scaledSize, y*scaledSize);
			}
		}

		mapFile.ignore();
		mapFile.close();
	}

	/*void AddTile(int srcX, int srcY, int xpos, int ypos) {
		TileComponent* t = new TileComponent(srcX, srcY, xpos, ypos, tileSetSize, mapScale, imageID);
		e->addComponent(typeid(TileComponent),t);//<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, imageID);
	}*/

	void update() override
	{

	}
	void draw() override
	{

		for (int y = 0; y < sizeY-1; y++) {
			for (int x = 0; x < sizeX; x++) {
				srcRect.x = (map[y][x]%tileSetColumns)*tileSize;
				srcRect.y = (map[y][x]/tileSetRows)*tileSize;
				destRect.x = x*destRect.w - Engine::instance().camera.x;
				destRect.y = y*destRect.h - Engine::instance().camera.y;

				SDL_RenderCopyEx(Engine::instance().renderer, texture->get(), &srcRect, &destRect, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}

	~MapComponent()
	{

	}
};

#endif