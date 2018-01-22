#pragma once

#include <iostream>
#include <lua.hpp>

void stackDump(lua_State *L);
void printLuaError(lua_State *L);
