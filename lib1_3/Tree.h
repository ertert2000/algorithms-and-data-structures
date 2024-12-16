#pragma once
#include <iostream>
#include <memory>
#include <unordered_set>
#include <iomanip>
#include <queue>
#include <cmath>
#include <random>

#include "TreeNode.h"


template <typename T>
class Tree 
{
private:
    const int maxrow = 20;
    const int maxcol = 80;
    const int offset = 40;

    std::shared_ptr<TreeNode<T>> root;

    int nodeCounter;

    char** SCREEN;

public:
    Tree();

    Tree(const Tree&) = delete;

    Tree(Tree&&) = delete;

    void addNode(int value);

    void addNodeHelper(std::shared_ptr<TreeNode<T>>& node, int value);

    void inOrderTraversal() const;

    void inOrderTraversalHelper(std::shared_ptr<TreeNode<T>> node) const;

    void printTreeHelper(std::ostream& sys, std::shared_ptr<TreeNode<T>> node) const;

    void OutTree();

    void clrscr();

    void OutNodes(std::shared_ptr<TreeNode<T>> v, int r, int c);

    void collectInOrderNodesFromLevelToBottom(std::shared_ptr<TreeNode<T>> node, int currentLevel, int startLevel, int maxLevel, std::vector<T>& result);

    std::vector<T> getNodesFromSecondLevelToBottom();

    void manualInput();

    void generateRandomValues(int n, int minValue, int maxValue);

    ~Tree();

private:
    int getHeight(const std::shared_ptr<TreeNode<T>>& node);
};

template <typename T>
Tree<T>::Tree() : root(nullptr), nodeCounter(0) 
{
    SCREEN = new char* [maxrow];

    for (int i = 0; i < maxrow; ++i)
        SCREEN[i] = new char[maxcol];
}

template <typename T>
void Tree<T>::addNodeHelper(std::shared_ptr<TreeNode<T>>& node, int value) 
{
    if (!node) 
    {
        node = std::make_shared<TreeNode<T>>(value);
        return;
    }
    if (value < node->value)
        addNodeHelper(node->left, value);
    else if (value > node->value)
        addNodeHelper(node->right, value);
}

template <typename T>
void Tree<T>::inOrderTraversalHelper(std::shared_ptr<TreeNode<T>> node) const 
{
    if (node) 
    {
        inOrderTraversalHelper(node->left);
        std::cout << node->value << " ";
        inOrderTraversalHelper(node->right);
    }
}

template <typename T>
void Tree<T>::printTreeHelper(std::ostream& sys, std::shared_ptr<TreeNode<T>> node) const 
{
    if (!node) return;

    int height = getHeight(node);
    int maxNodes = std::pow(2, height) - 1;
    int width = 4 * maxNodes;

    std::queue<std::shared_ptr<TreeNode<T>>> q;
    q.push(node);

    for (int level = 0; level < height; ++level) 
    {
        int levelNodes = std::pow(2, level);
        int spaceBetween = width / levelNodes;

        for (int i = 0; i < levelNodes; ++i) 
        {
            std::shared_ptr<TreeNode<T>> current = q.front();
            q.pop();

            if (current) 
            {
                sys << std::setw(spaceBetween / 2) << ""
                    << current->value
                    << std::setw(spaceBetween / 2) << "";

                q.push(current->left);
                q.push(current->right);
            }
            else 
            {
                sys << std::setw(spaceBetween) << "";
                q.push(nullptr);
                q.push(nullptr);
            }
        }
        sys << std::endl;
    }
}

template <typename T>
int Tree<T>::getHeight(const std::shared_ptr<TreeNode<T>>& node) 
{
    if (!node) 
        return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

template <typename T>
void Tree<T>::addNode(int value) 
{
    addNodeHelper(root, value);
}

template <typename T>
void Tree<T>::inOrderTraversal() const 
{
    inOrderTraversalHelper(root);
    std::cout << std::endl;
}

template <typename T>
void Tree<T>::OutNodes(std::shared_ptr<TreeNode<T>> v, int r, int c)
{
    if (!v || r >= maxrow || c < 1 || c >= maxcol) return;

    SCREEN[r - 1][c - 1] = v->value;
    if (v->left)
    {
        SCREEN[r][c - 2] = '/';
        OutNodes(v->left, r + 2, c - (offset >> r));
    }
    if (v->right)
    {
        SCREEN[r][c] = '\\';
        OutNodes(v->right, r + 2, c + (offset >> r));
    }
}

template <typename T>
void Tree<T>::OutTree() 
{
    clrscr();
    OutNodes(root, 1, offset);
    for (int i = 0; i < maxrow; i++) 
    {
        SCREEN[i][maxcol - 1] = 0;
        std::cout << SCREEN[i] << "\n";
    }
    std::cout << "\n";
}

template <typename T>
void Tree<T>::clrscr() 
{
    for (int i = 0; i < maxrow; i++)
        memset(SCREEN[i], '.', maxcol);
}

template <typename T>
void Tree<T>::collectInOrderNodesFromLevelToBottom(std::shared_ptr<TreeNode<T>> node, int currentLevel, int startLevel, int maxLevel, std::vector<T>& result)
{
    if (!node || currentLevel > maxLevel)
        return;

    collectInOrderNodesFromLevelToBottom(node->left, currentLevel + 1, startLevel, maxLevel, result);

    if (currentLevel >= startLevel)
        result.push_back(node->value);

    collectInOrderNodesFromLevelToBottom(node->right, currentLevel + 1, startLevel, maxLevel, result);
}

template <typename T>
std::vector<T> Tree<T>::getNodesFromSecondLevelToBottom() 
{
    std::vector<T> result;
    int maxDepth = getHeight(root);
    int startLevel = 2;

    collectInOrderNodesFromLevelToBottom(root, 0, startLevel, maxDepth - 1, result);

    return result;
}

template <typename T>
void Tree<T>::manualInput() 
{
    int n;
    std::cout << "Enter the number of nodes: ";
    std::cin >> n;

    if (n < 0 || n == 0)
        return;

    std::cout << "Enter node values: ";
    for (int i = 0; i < n; ++i) 
    {
        T value;
        std::cin >> value;
        addNode(value);
    }
}

template <typename T>
void Tree<T>::generateRandomValues(int n, int minValue, int maxValue)
{
    std::unordered_set<char> uniqueNumbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(minValue, maxValue);

    std::cout << "Generation " << n << " random values: ";

    while (uniqueNumbers.size() != n)
        uniqueNumbers.insert(distrib(gen));
    
    for (char num : uniqueNumbers)
    {
        std::cout << num << " ";
        addNode(num);
    }

    std::cout << std::endl;
}

template <typename T>
Tree<T>::~Tree()
{
    for (int i = 0; i < maxrow; ++i)
        delete[] SCREEN[i];

    delete[] SCREEN;
}