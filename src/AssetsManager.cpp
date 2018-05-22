
#include <string>
#include <iostream>

#include "AssetsManager.h"
#include "LuaHelperFunctions.h"
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

using namespace std;

AssetsManager::AssetsManager() {
	loadImages();
}

void AssetsManager::loadImages() {
	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	loadScript(L, "assets/images/images.lua");
	loadGetKeysFunction(L);

	auto v = getTableKeys(L, "images");
	luabridge::LuaRef t = luabridge::getGlobal(L, "images");

	for (auto str : v) {
		luabridge::LuaRef s = t[str];
		if (s.isNil()) {
			std::cout << "Variable not found!" << std::endl;
		}
		else {
			if (s.isString()) {
				string filename = s.cast<string>();
				string path = "assets/images/" + filename;
				//cout << str << " = " << path << endl;
				textures[str] = new Texture(path.c_str());
			}
		}
	}

	//luabridge::lua_close(L);
}

void AssetsManager::loadMusics() {
	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	loadScript(L, "assets/musics/musics.lua");
	loadGetKeysFunction(L);

	auto v = getTableKeys(L, "musics");
	luabridge::LuaRef t = luabridge::getGlobal(L, "musics");

	for (auto str : v) {
		luabridge::LuaRef s = t[str];
		if (s.isNil()) {
			std::cout << "Variable not found!" << std::endl;
		}
		else {
			if (s.isString()) {
				string filename = s.cast<string>();
				string path = "assets/musics/" + filename;
				cout << str << " = " << path << endl;

			}
		}
	}

	//luabridge::lua_close(L);
}

void AssetsManager::loadSounds() {
	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	loadScript(L, "assets/sound/sound.lua");
	loadGetKeysFunction(L);

	auto v = getTableKeys(L, "sound");
	luabridge::LuaRef t = luabridge::getGlobal(L, "sound");

	for (auto str : v) {
		luabridge::LuaRef s = t[str];
		if (s.isNil()) {
			std::cout << "Variable not found!" << std::endl;
		}
		else {
			if (s.isString()) {
				string filename = s.cast<string>();
				string path = "assets/sound/" + filename;
				cout << str << " = " << path << endl;

			}
		}
	}

	//luabridge::lua_close(L);
}

void AssetsManager::loadFonts() {
	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	loadScript(L, "assets/fonts/fonts.lua");
	loadGetKeysFunction(L);

	auto v = getTableKeys(L, "fonts");
	luabridge::LuaRef t = luabridge::getGlobal(L, "fonts");

	for (auto str : v) {
		luabridge::LuaRef s = t[str];
		if (s.isNil()) {
			std::cout << "Variable not found!" << std::endl;
		}
		else {
			if (s.isString()) {
				string filename = s.cast<string>();
				string path = "assets/fonts/" + filename;
				cout << str << " = " << path << endl;

			}
		}
	}

	//luabridge::lua_close(L);
}

Texture* AssetsManager::getTexture(string code) {
	return textures[code];
}

AssetsManager::~AssetsManager() {

}