#include "Tree.h"

Tree::Tree() : root(nullptr)
{
    SCREEN = new char* [maxrow];

    for (int i = 0; i < maxrow; ++i)
        SCREEN[i] = new char[maxcol];
}

void Tree::addNodeHelper(std::shared_ptr<TreeNode>& node, int value)
{
	if (!node)
		node = std::make_shared<TreeNode>(value);
	else if (value < node->value)
		addNodeHelper(node->left, value);
	else
		addNodeHelper(node->right, value);
}

void Tree::inOrderTraversalHelper(std::shared_ptr<TreeNode> node) const
{
	if (node)
	{
		inOrderTraversalHelper(node->left);
		std::cout << node->value << " ";
		inOrderTraversalHelper(node->right);
	}
}

void Tree::printTreeHelper(std::ostream& sys, std::shared_ptr<TreeNode> node) const
{
    if (!node) return;

    int height = getHeight(node);
    int maxNodes = std::pow(2, height) - 1;
    int width = 4 * maxNodes;

    std::queue<std::shared_ptr<TreeNode>> q;
    q.push(node);

    for (int level = 0; level < height; ++level) 
    {
        int levelNodes = std::pow(2, level);
        int spaceBetween = width / levelNodes;

        for (int i = 0; i < levelNodes; ++i) 
        {
            std::shared_ptr<TreeNode> current = q.front();
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

int Tree::getHeight(const std::shared_ptr<TreeNode>& node)
{
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

void Tree::addNode(int value)
{
	addNodeHelper(root, value);
}

void Tree::inOrderTraversal() const
{
	inOrderTraversalHelper(root);
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& sys, const Tree& tree)
{
    tree.printTreeHelper(sys, tree.root);
    return sys;
}

void Tree::OutTree()
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

void Tree::clrscr()
{
    for (int i = 0; i < maxrow; i++)
        memset(SCREEN[i], '.', maxcol);
}

void Tree::OutNodes(std::shared_ptr<TreeNode> v, int r, int c)
{
    if (!v || r >= maxrow || c < 1 || c >= maxcol) return;

    SCREEN[r - 1][c - 1] = '0' + v->value;
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

void Tree::collectInOrderNodesUpToLevel(std::shared_ptr<TreeNode> node, int currentLevel, int maxLevel, std::vector<int>& result)
{
    if (!node || currentLevel > maxLevel)
        return;

    collectInOrderNodesUpToLevel(node->left, currentLevel + 1, maxLevel, result);

    if (currentLevel <= maxLevel)
        result.push_back(node->value);

    collectInOrderNodesUpToLevel(node->right, currentLevel + 1, maxLevel, result);
}

std::vector<int> Tree::getNodesInOrderUpToLevel2()
{
    std::vector<int> result;
    collectInOrderNodesUpToLevel(root, 0, 2, result);
    return result;
}

void Tree::manualInput()
{
    int n;
    std::cout << "Enter the number of nodes: ";
    std::cin >> n;

    if (n < 0 || n == 0)
        return;

    std::cout << "Enter node values: ";
    for (int i = 0; i < n; ++i) 
    {
        int value;
        std::cin >> value;
        addNode(value);
    }
}

void Tree::generateRandomValues(int n, int minValue, int maxValue)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(minValue, maxValue);

    std::cout << "Generation " << n << " random values: ";
    for (int i = 0; i < n; ++i) 
    {
        int value = distrib(gen);
        std::cout << value << " ";
        addNode(value);
    }
    std::cout << std::endl;
}

Tree::~Tree()
{
    for (int i = 0; i < maxrow; ++i) 
        delete[] SCREEN[i];

    delete[] SCREEN;
}

