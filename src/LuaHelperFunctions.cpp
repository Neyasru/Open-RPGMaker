
#include "LuaHelperFunctions.h"
#include "ECS/ECS.h"

#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#define ADD_FUNCTION(x) addFunction(#x, &LuaEntityHandle::x)

using namespace luabridge;

bool loadScript(luabridge::lua_State* L, const std::string& scriptFilename) {
	if (luaL_dofile(L, scriptFilename.c_str()) == 0) { // script has opened
		return true;
    } else {
        std::cout << "Error, can't open script "<< scriptFilename << std::endl;
		return false;
    }
}

void loadLuaFunctions(luabridge::lua_State* L) {
	getGlobalNamespace(L)
		.beginClass<LuaEntityHandle>("LuaEntityHandle")
		.ADD_FUNCTION(setAnimation)
		.endClass();
}

void loadGetKeysFunction(luabridge::lua_State* L) {
    std::string code =
        R"(function getKeys(t)
        s = {}
        for k, v in pairs(t) do
            table.insert(s, k)
            end 
        return s 
        end)";
    luaL_dostring(L, code.c_str());
}

std::vector<std::string> getTableKeys(luabridge::lua_State* L, const std::string& name) {
	lua_getglobal(L, "getKeys"); // get function
    if (lua_isnil(L, -1)) {
        std::cout << "Get keys function is not loaded. Loading..." << std::endl;
        loadGetKeysFunction(L);
        lua_getglobal(L, "getKeys");
    }
	
	lua_gettostack(L, name);
	luabridge::lua_pcall(L, 1, 1, 0);
	std::string type = luaL_typename(L, 1);
	if (type == "table") {
		std::vector<std::string> keys;

		lua_pushnil(L);

		while (lua_next(L, -2)) { // get values one by one
			if (lua_type(L, -1) == LUA_TSTRING) { // check if key is a string
				keys.push_back(luabridge::lua_tostring(L, -1));
			}
			luabridge::lua_pop(L, 1);
		}

		lua_settop(L, 0); // remove s table from stack 
		return keys;
	}
	else {
		lua_settop(L, 0); // remove s table from stack 
		return std::vector<std::string>();
	}
}

void lua_gettostack(luabridge::lua_State* L, const std::string& variableName) {
    int level = 0;
    std::string var = "";
    for (unsigned int i = 0; i < variableName.size(); i++) {
        if (variableName.at(i) == '.') {
            if (level == 0) {
                lua_getglobal(L, var.c_str());
            } else {
                lua_getfield(L, -1, var.c_str());
            }
 
            if (lua_isnil(L, -1)) {
                std::cout << "Error, can't get " << variableName << std::endl;
                return;
            } else {
                var = "";
                level++;
            }
        } else {
            var += variableName.at(i);
        }
    }
    if (level == 0) {
        lua_getglobal(L, var.c_str());
    } else {
        lua_getfield(L, -1, var.c_str());
    }
	
	 if (level == 0) { return; } // no need to remove anything
 
    int tableIndex = luabridge::lua_gettop(L) - level;
	lua_replace(L, tableIndex);
	luabridge::lua_settop(L, tableIndex);
}