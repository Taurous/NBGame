#pragma once
#include <iostream>
#include <lua.hpp>
#include "LuaUtil.h"

const int MAX_BRANCHES = 32;
const int MAX_NUM_MULTI_CHOICE = 4;

class NodeManager;

class StoryNode
{
public:
	StoryNode(NodeManager *node_manager, int id, int prev_node);
	void handleInput(std::string);
	~StoryNode();

protected:
	unsigned int m_id;
	unsigned int m_previous_node_id;
	unsigned int m_next_node_id[MAX_BRANCHES];

	lua_State *L;
	NodeManager *m_node_manager;
};