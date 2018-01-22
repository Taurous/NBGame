#include "LuaUtil.h"

void stackDump(lua_State *L)
{
	int top = lua_gettop(L);

	std::cout << "Dumping Lua stack, stack size: " << top << std::endl;
	for (int i = 1; i <= top; i++)
	{
		int type = lua_type(L, i);
		switch (type)
		{
		case LUA_TSTRING:
			std::cout << "     " << i << ": String: " << lua_tostring(L, i) << std::endl;
			break;
		case LUA_TBOOLEAN:
			std::cout << "     " << i << ": Boolean: " << (lua_toboolean(L, i) ? "True" : "False") << std::endl;
			break;
		case LUA_TNUMBER:
			std::cout << "     " << i << ": Number: " << lua_tonumber(L, i) << std::endl;
			break;
		default:
			std::cout << "     " << i << ": " << lua_typename(L, type) << std::endl;
			break;
		}
	}
	std::cout << std::endl;
}

void printLuaError(lua_State *L)
{
	std::cout << "Lua Error: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);

	stackDump(L);
}