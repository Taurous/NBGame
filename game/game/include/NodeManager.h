#pragma once

#include <list>
#include <memory>
#include "StoryNode.h"

class NodeManager
{
public:
	NodeManager(int id);
	~NodeManager();

	void pushNode(int id, int prev_id);
	void handleInput(std::string s);
	void cleanNodeList();
private:
	std::list<std::unique_ptr<StoryNode>> node_list;
};

