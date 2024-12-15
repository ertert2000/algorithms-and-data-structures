#include <iostream>
#include <random>
#include "Tree.h"
#include "TreeNode.h"



int main()
{
    int choise = 0;
	Tree tree;

    while (!choise)
    {
        std::cout << "#==========================#" << std::endl;
        std::cout << "1 - Create a tree manually" << std::endl;
        std::cout << "2 - Generate tree" << std::endl;
        std::cout << "#==========================#" << std::endl;
        std::cin >> choise;
        switch (choise)
        {
        case 1:
            system("cls");
            tree.manualInput();
            break;
        case 2:
            system("cls");
            tree.generateRandomValues(10, 1, 9);
            break;
        default:
            system("cls");
            break;
        }
    }

    tree.OutTree(); std::cout << std::endl << std::endl;

    std::cout << "in-order traversal:"; tree.inOrderTraversal();

    auto nodes = tree.getNodesInOrderUpToLevel2();
    std::cout << "Nodes up to level 2 (in-order): ";
    for (int val : nodes)
        std::cout << val << " ";

    std::cout << std::endl;

    std::cout << "Quantity nodes up to level 2: " << nodes.size();

	return 0;
}