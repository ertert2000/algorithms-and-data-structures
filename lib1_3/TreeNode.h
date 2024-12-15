#pragma once
#include <memory>

class TreeNode
{
public:
	int value;
	std::shared_ptr<TreeNode> left;
	std::shared_ptr<TreeNode> right;

	TreeNode(int val);
	TreeNode(const TreeNode&) = delete;
	TreeNode(TreeNode&&) = delete;

	~TreeNode();
};

