#pragma once
#include <memory>

template <typename T>
class TreeNode
{
public:
	T value;
	std::shared_ptr<TreeNode<T>> left, right;

	TreeNode(T value);
	TreeNode(const TreeNode&) = delete;
	TreeNode(TreeNode&&) = delete;

	~TreeNode();
};

template<typename T>
TreeNode<T>::TreeNode(T value) : value(value), left(nullptr), right(nullptr) {}

template<typename T>
TreeNode<T>::~TreeNode() {}