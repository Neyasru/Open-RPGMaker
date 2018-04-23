#ifndef _LUAHELPERFUNC_H_
#define _LUAHELPERFUNC_H_

#include <string>
#include <vector>
#include <LuaBridge/LuaBridge.h>

struct lua_State;

bool loadScript(luabridge::lua_State* L, const std::string& filename); // will be explained later

void loadLuaFunctions(luabridge::lua_State* L);

void loadGetKeysFunction(luabridge::lua_State* L);

void lua_gettostack(luabridge::lua_State* L, const std::string& variableName); // ...and this one
    
std::vector<std::string> getTableKeys(luabridge::lua_State* L, const std::string& name);



#endif