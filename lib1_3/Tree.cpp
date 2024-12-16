//#include "Tree.h"
//
//template <typename T>
//Tree<T>::Tree() : root(nullptr), nodeCounter(0) {
//    SCREEN = new char* [maxrow];
//
//    for (int i = 0; i < maxrow; ++i)
//        SCREEN[i] = new char[maxcol];
//}
//
//template <typename T>
//void Tree<T>::addNodeHelper(std::shared_ptr<TreeNode<T>>& node, int value) {
//    if (!node)
//    {
//        // Присваиваем уникальный идентификатор узлу
//        node = std::make_shared<TreeNode<T>>(++nodeCounter);
//    }
//    else if (value < node->value)
//        addNodeHelper(node->left, value);
//    else
//        addNodeHelper(node->right, value);
//}
//
//template <typename T>
//void Tree<T>::inOrderTraversalHelper(std::shared_ptr<TreeNode<T>> node) const {
//    if (node) {
//        inOrderTraversalHelper(node->left);
//        std::cout << node->value << " ";
//        inOrderTraversalHelper(node->right);
//    }
//}
//
//template <typename T>
//void Tree<T>::printTreeHelper(std::ostream& sys, std::shared_ptr<TreeNode<T>> node) const {
//    if (!node) return;
//
//    int height = getHeight(node);
//    int maxNodes = std::pow(2, height) - 1;
//    int width = 4 * maxNodes;
//
//    std::queue<std::shared_ptr<TreeNode<T>>> q;
//    q.push(node);
//
//    for (int level = 0; level < height; ++level) {
//        int levelNodes = std::pow(2, level);
//        int spaceBetween = width / levelNodes;
//
//        for (int i = 0; i < levelNodes; ++i) {
//            std::shared_ptr<TreeNode<T>> current = q.front();
//            q.pop();
//
//            if (current) {
//                sys << std::setw(spaceBetween / 2) << ""
//                    << current->value
//                    << std::setw(spaceBetween / 2) << "";
//
//                q.push(current->left);
//                q.push(current->right);
//            }
//            else {
//                sys << std::setw(spaceBetween) << "";
//                q.push(nullptr);
//                q.push(nullptr);
//            }
//        }
//        sys << std::endl;
//    }
//}
//
//template <typename T>
//int Tree<T>::getHeight(const std::shared_ptr<TreeNode<T>>& node) {
//    if (!node) return 0;
//    return 1 + std::max(getHeight(node->left), getHeight(node->right));
//}
//
//template <typename T>
//void Tree<T>::addNode(int value) {
//    addNodeHelper(root, value);
//}
//
//template <typename T>
//void Tree<T>::inOrderTraversal() const {
//    inOrderTraversalHelper(root);
//    std::cout << std::endl;
//}
//
//template <typename T>
//void Tree<T>::OutNodes(std::shared_ptr<TreeNode<T>> v, int r, int c, int level) {
//    if (!v || r >= maxrow || c < 1 || c >= maxcol) return;
//
//    // Присваиваем уникальное значение узлу в зависимости от уровня и позиции
//    SCREEN[r - 1][c - 1] = '0' + (v->value + level); // Используем level для уникальности
//    if (v->left) {
//        SCREEN[r][c - 2] = '/';
//        OutNodes(v->left, r + 2, c - (offset >> r), level + 1); // Увеличиваем уровень
//    }
//    if (v->right) {
//        SCREEN[r][c] = '\\';
//        OutNodes(v->right, r + 2, c + (offset >> r), level + 1); // Увеличиваем уровень
//    }
//}
//
//template <typename T>
//void Tree<T>::OutTree() {
//    clrscr();
//    OutNodes(root, 1, offset, 0); // Передаем начальный уровень как 0
//    for (int i = 0; i < maxrow; i++) {
//        SCREEN[i][maxcol - 1] = 0;
//        std::cout << SCREEN[i] << "\n";
//    }
//    std::cout << "\n";
//}
//
//template <typename T>
//void Tree<T>::clrscr() {
//    for (int i = 0; i < maxrow; i++)
//        memset(SCREEN[i], '.', maxcol);
//}
//
//template <typename T>
//void Tree<T>::collectInOrderNodesUpToLevel(std::shared_ptr<TreeNode<T>> node, int currentLevel, int maxLevel, std::vector<T>& result) {
//    if (!node || currentLevel > maxLevel)
//        return;
//
//    collectInOrderNodesUpToLevel(node->left, currentLevel + 1, maxLevel, result);
//
//    if (currentLevel <= maxLevel)
//        result.push_back(node->value);
//
//    collectInOrderNodesUpToLevel(node->right, currentLevel + 1, maxLevel, result);
//}
//
//template <typename T>
//std::vector<T> Tree<T>::getNodesInOrderUpToLevel2() {
//    std::vector<T> result;
//    collectInOrderNodesUpToLevel(root, 0, 2, result);
//    return result;
//}
//
//template <typename T>
//void Tree<T>::manualInput() {
//    int n;
//    std::cout << "Enter the number of nodes: ";
//    std::cin >> n;
//
//    if (n < 0 || n == 0)
//        return;
//
//    std::cout << "Enter node values: ";
//    for (int i = 0; i < n; ++i) {
//        int value;
//        std::cin >> value;
//        addNode(value);
//    }
//}
//
//template <typename T>
//void Tree<T>::generateRandomValues(int n, int minValue, int maxValue) 
//{
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> distrib(minValue, maxValue);
//
//    std::cout << "Generation " << n << " random values: ";
//    for (int i = 0; i < n; ++i) 
//    {
//        int value = distrib(gen);
//        std::cout << value << " ";
//        addNode(value);
//    }
//    std::cout << std::endl;
//}
//
//template <typename T>
//Tree<T>::~Tree() 
//{
//    for (int i = 0; i < maxrow; ++i)
//        delete[] SCREEN[i];
//
//    delete[] SCREEN;
//}
//
