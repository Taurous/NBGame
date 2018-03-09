#include "NodeManager.h"

NodeManager::NodeManager(int id)
{
	pushNode(id, 0);
}

NodeManager::~NodeManager()
{
	node_list.clear();
}

void NodeManager::pushNode(int id, int prev_id)
{
	std::unique_ptr<StoryNode> node_ptr = std::make_unique<StoryNode>(this, id, prev_id);

	node_list.push_back(std::move(node_ptr));
}

int NodeManager::getCurrentNodeID()
{
	return node_list.back()->getID();
}

int NodeManager::handleInput(std::string s)
{
	return node_list.back()->handleInput(s);
}

void NodeManager::cleanNodeList()
{
	if (node_list.size() > 1)
	{
		node_list.pop_front();
	}
}

const std::string & NodeManager::getImagePath()
{
	return node_list.back()->getImagePath();
}
