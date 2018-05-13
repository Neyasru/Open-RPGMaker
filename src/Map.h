#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <LuaBridge/LuaBridge.h>
#include "LuaHelperFunctions.h"

class Entity;
class EntityManager;
class MapManager;

typedef std::vector<std::vector<Entity*>> Layer;

class Map {
private:
	MapManager* mapManager;
	std::vector<Layer> tile_map;
	int sizeX = 1, sizeY = 1;
	int mapScale = 1;
	int layers;
public:
	Map(luabridge::LuaRef& mapTable, MapManager* mm);
	void loadMap(std::string file);
	void addTile();
	void addLayer();
	void drawLayer(int layer);
	
	Entity* getTile(int x, int y);
};

class MapManager {
private:
	EntityManager* entityManager;
	int actualMap;
	int totalMaps;
	std::map<int, std::string> tilesReferences;
	std::vector<std::unique_ptr<Map>> maps;
	
public:
	MapManager(EntityManager *em);
	EntityManager* getEntityManager() {return entityManager;}
	void loadTileReferences(luabridge::lua_State* L);
	void addMaps(luabridge::lua_State* L);
	std::string getTileName(int tileNum){ return tilesReferences[tileNum];}

	void drawLayer(int layer);
};

#endif
