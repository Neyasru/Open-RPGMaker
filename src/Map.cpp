#include "Map.h"
#include "ECS/Components.h"

Map::Map(luabridge::LuaRef& mapTable, MapManager* mm){
	this->mapManager = mm;
	
	int error = false;
	using namespace luabridge;
	auto layersRef = mapTable["layers"];
	auto sizeXRef = mapTable["sizeX"];
	auto sizeYRef = mapTable["sizeY"];
	auto mapScaleRef = mapTable["mapScale"];
	auto pathRef = mapTable["path"];
	
	if (layersRef.isNumber()) {
		layers = layersRef.cast<int>();
	}
	else {
		std::cout << "Error, Map.layersRef is not a number!" << std::endl;
		error = true;
	}
	
	if (sizeXRef.isNumber()) {
		sizeX = sizeXRef.cast<int>();
	}
	else {
		std::cout << "Error, Map.sizeXRef is not a number!" << std::endl;
		error = true;
	}
	
	if (sizeYRef.isNumber()) {
		sizeY = sizeYRef.cast<int>();
	}
	else {
		std::cout << "Error, Map.sizeYRef is not a number!" << std::endl;
		error = true;
	}
	
	if (mapScaleRef.isNumber()) {
		mapScale = mapScaleRef.cast<int>();
	}
	else {
		std::cout << "Error, Map.mapScale is not a number!" << std::endl;
		error = true;
	}
	
	if(pathRef.isString()){
		loadMap(pathRef.cast<std::string>());
	}
	else {
		std::cout << "Error, Map.path is not a string!" << std::endl;
		error = true;
	}
}

void Map::loadMap(std::string file){
		std::ifstream mapFile(file);
	
		int srcX, srcY;


		luabridge::lua_State* L = luabridge::luaL_newstate();
		luabridge::luaL_openlibs(L);
		loadLuaFunctions(L);
		loadGetKeysFunction(L);
		if (loadScript(L, "assets/tiles/tiles.lua")) {
			for(int z = 0; z < layers; z++){
				Layer aux_Layer;
				for (int y = 0; y < sizeY-1; y++){
					std::vector<Entity*> aux_Row;
					for (int x = 0; x < sizeX-1; x++){
						std::string input;
						getline(mapFile, input, ',');
						int val = std::stoi(input);
						
						Entity *aux_ent = &(mapManager->getEntityManager()->addEntity(L, mapManager->getTileName(val)));
						if (aux_ent->get<TransformComponent>() != NULL) {
							aux_ent->get<TransformComponent>()->position.x = x;
							aux_ent->get<TransformComponent>()->position.y = y;
						}
						else {
							std::cout << mapManager->getTileName(val) << " tile not loaded!" << endl;
						}
						aux_Row.push_back(aux_ent);
						//tile_map[x][y][z] = &(mapManager->getEntityManager()->addEntity(L, mapManager->getTileName(val))); //crear una funcio dins de map manager que s'encarregui de aixo
					
						//map[y][x] = val;
						//srcX = val% tileSetSize;
						//srcY = val/ tileSetSize;
						//addTile(srcX, srcY, x*scaledSize, y*scaledSize);
					}
					aux_Layer.push_back(aux_Row);
				}
				tile_map.push_back(aux_Layer);
			}
		}

		mapFile.ignore();
		mapFile.close();
}

void Map::addTile(){
	
}

void Map::addLayer(){
	
}

void Map::drawLayer(int layer) {

}

MapManager::MapManager(EntityManager *em) { 
	entityManager = em; 
	actualMap = 0;
}

void MapManager::loadTileReferences(luabridge::lua_State* L){
		const std::string type = "tiles";
		auto v = getTableKeys(L, type);
		luabridge::LuaRef tileTable = getGlobal(L, type.c_str());
		for (auto& tileName : v) {
			tilesReferences[tileTable[tileName].cast<int>()] = tileName;
			std::cout << tileName << "==" << tileTable[tileName].cast<int>() << std::endl;
		}	
}

void MapManager::addMaps(luabridge::lua_State* L) {
	using namespace luabridge;
	
	const std::string type = "maps";
	auto v = getTableKeys(L, type);
	luabridge::LuaRef mapsTable = getGlobal(L, type.c_str());
	for (auto& mapsName : v) {
		luabridge::LuaRef mapTable = mapsTable[mapsName];
		Map* m = new Map(mapTable, this);
		
		//m->init();
		std::unique_ptr<Map> uPtr{ m };
		maps.emplace_back(std::move(uPtr));
		std::cout << "Added " << mapsName << " to " << type << std::endl;

	}
}

void MapManager::drawLayer(int layer) {
	maps[actualMap]->drawLayer(layer);
}