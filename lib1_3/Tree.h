#pragma once
#include <iostream>
#include <memory>
#include <iomanip>
#include <queue>
#include <cmath>
#include <random>

#include "TreeNode.h"


class Tree
{
protected:
	const int maxrow = 20;
	const int maxcol = 80;
	char** SCREEN;
	const int offset = 40;

	std::shared_ptr<TreeNode> root;

	void addNodeHelper(std::shared_ptr<TreeNode>& node, int value);

	void inOrderTraversalHelper(std::shared_ptr<TreeNode> node) const;

	void printTreeHelper(std::ostream& os, std::shared_ptr<TreeNode> node) const;

	static int getHeight(const std::shared_ptr<TreeNode>& node);

	void collectInOrderNodesUpToLevel(std::shared_ptr<TreeNode> node, int currentLevel, int maxLevel, std::vector<int>& result);

public:
	Tree();

	Tree(const Tree&) = delete;	   

	Tree(Tree&&) = delete;

	void addNode(int value);

	void inOrderTraversal() const;

	friend std::ostream& operator<<(std::ostream& os, const Tree& tree);

	void OutTree();

	void clrscr();

	void OutNodes(std::shared_ptr<TreeNode> v, int r, int c);

	std::vector<int> getNodesInOrderUpToLevel2();

	void manualInput();

	void generateRandomValues(int n, int minValue, int maxValue);

	~Tree();
};

