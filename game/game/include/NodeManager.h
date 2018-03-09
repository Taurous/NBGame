#pragma once

#include <string>
#include <list>
#include <memory>
#include "StoryNode.h"

class NodeManager
{
public:
	NodeManager(int id);
	~NodeManager();

	void pushNode(int id, int prev_id);
	int getCurrentNodeID();
	int handleInput(std::string s);
	void cleanNodeList();

	const std::string &getImagePath();
private:
	std::list<std::unique_ptr<StoryNode>> node_list;
};

