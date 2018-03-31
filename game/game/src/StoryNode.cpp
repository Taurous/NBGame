#include "StoryNode.h"
#include "NodeManager.h"

StoryNode::StoryNode(NodeManager *node_manager, int id, int prev_node) : m_node_manager(node_manager), m_id(id), m_previous_node_id(prev_node), m_next_node_id{0}
{
	L = luaL_newstate();
	luaL_openlibs(L);

	char filenamebuffer[32];
	sprintf_s(filenamebuffer, "scripts/script_%i.lua", id);

	if (luaL_loadfile(L, filenamebuffer) != LUA_OK)
	{
		printLuaError(L);
	}
	else if (lua_pcall(L, 0, 0, 0) != LUA_OK)
	{
		printLuaError(L);
	}

	if (luaL_loadfile(L, "scripts/common.lua") != LUA_OK)
	{
		printLuaError(L);
	}
	else if (lua_pcall(L, 0, 0, 0) != LUA_OK)
	{
		printLuaError(L);
	}
}

int StoryNode::handleInput(std::string s)
{
	lua_getglobal(L, "interpret");
	lua_pushstring(L, s.c_str());
	if (lua_pcall(L, 1, 1, 0) != LUA_OK)
	{
		printLuaError(L);
		lua_pop(L, 2);
		return 0;
	}

	if (!lua_isnil(L, -1))
	{
		int i = lua_tonumber(L, -1);

		lua_pushinteger(L, i);
		lua_setglobal(L, "node_id");

		lua_getglobal(L, "func");
		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printLuaError(L);
			lua_pop(L, 1);
		}

		return i;
	}
	else
	{
		return -1;
	}
}

int StoryNode::getID()
{
	return m_id;
}

StoryNode::~StoryNode()
{
	lua_close(L);
	L = nullptr;
}

/*lua_getglobal(L, "v");
int result;
int var = lua_tonumberx(L, -1, &result); // This works (when the pcall works of course)
if (result)
{
std::cout << "Variable: " << lua_tonumber(L, -1) << std::endl;

}
else
{
std::cout << "Variable 'v' does not exist." << std::endl;
}
lua_pop(L, 1);*/