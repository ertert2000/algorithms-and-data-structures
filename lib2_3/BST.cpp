#include "BST.h"


BSTListStructure::~BSTListStructure() { clear(root); }

BSTListStructure::BSTListStructure(BSTListStructure&& other) noexcept
{
    root = other.root;
    sequence = std::move(other.sequence);
    other.root = nullptr;
}

void BSTListStructure::insertUnique(int value)
{
    if (!exists(value))
        root = insert(root, value);
}

BSTListStructure& BSTListStructure::operator=(BSTListStructure&& other) noexcept
{
    if (this != &other)
    {
        clear(root);
        root = other.root;
        sequence = std::move(other.sequence);
        other.root = nullptr;
    }
    return *this;
}

void BSTListStructure::addToSequence(int value)
{
    Node* found = find(root, value);
    if (found)
        sequence.push_back(found);
}

void BSTListStructure::printTree() const
{
    printTreeHelper(root, 0);
}

void BSTListStructure::printSequence() const
{
    for (auto node : sequence)
    {
        if (node) std::cout << node->value << ' ';
        else std::cout << "[nullptr] ";
    }
    std::cout << '\n';
}

bool BSTListStructure::exists(int value) const
{
    return find(root, value) != nullptr;
}

BSTListStructure BSTListStructure::intersect(const BSTListStructure& a, const BSTListStructure& b)
{
    BSTListStructure result;

    for (auto node : a.sequence)
        if (node && b.exists(node->value)) result.insertUnique(node->value);

    result.refreshSequence();
    return result;
}

BSTListStructure BSTListStructure::unify(const BSTListStructure& a, const BSTListStructure& b)
{
    BSTListStructure result;

    for (auto node : a.sequence)
        if (node)
            result.insertUnique(node->value);

    for (auto node : b.sequence)
        if (node)
            result.insertUnique(node->value);

    result.refreshSequence();
    return result;
}

BSTListStructure BSTListStructure::xorSet(const BSTListStructure& a, const BSTListStructure& b)
{
    BSTListStructure result;

    std::set<int> onlyA, onlyB;

    for (auto node : a.sequence)
        if (node && !b.exists(node->value))
            onlyA.insert(node->value);

    for (auto node : b.sequence)
        if (node && !a.exists(node->value))
            onlyB.insert(node->value);

    for (int v : onlyA)
        result.insertUnique(v);

    for (int v : onlyB)
        result.insertUnique(v);

    result.refreshSequence();
    return result;
}

BSTListStructure BSTListStructure::mergeSeq(const BSTListStructure& a, const BSTListStructure& b)
{
    BSTListStructure result;
    result.copyTree(a);
    for (auto node : a.sequence)
        if (node)
            result.sequence.push_back(result.find(result.root, node->value));
    for (auto node : b.sequence)
        if (node)
            result.sequence.push_back(result.find(result.root, node->value));

    return result;
}

BSTListStructure BSTListStructure::exclSeq(const BSTListStructure& a, const BSTListStructure& b)
{
    BSTListStructure result;
    result.copyTree(a);

    for (auto node : a.sequence)
        if (node && !b.exists(node->value))
            result.sequence.push_back(result.find(result.root, node->value));

    return result;
}

BSTListStructure BSTListStructure::concatSeq(const BSTListStructure& a, const BSTListStructure& b)
{
    BSTListStructure result;
    result.copyTree(a);

    for (auto node : a.sequence)
        if (node)
            result.sequence.push_back(result.find(result.root, node->value));

    for (auto node : b.sequence)
        if (node)
            result.sequence.push_back(result.find(result.root, node->value));

    return result;
}

BSTListStructure BSTListStructure::generate(int count, int universe)
{
    BSTListStructure obj;
    std::srand(std::time(0));
    std::set<int> used;

    while (obj.sequence.size() < static_cast<size_t>(count))
    {
        int v = rand() % universe;
        if (!obj.exists(v))
        {
            obj.insertUnique(v);
            Node* node = obj.find(obj.root, v);
            if (node)
                obj.sequence.push_back(node);
        }
    }
    return obj;
}

BSTListStructure BSTListStructure::simpleEval(char op, const BSTListStructure& a, const BSTListStructure& b)
{
    switch (op)
    {
    case '+': return unify(a, b);
    case '*': return intersect(a, b);
    case '-': return exclSeq(a, b);
    case '/': return xorSet(a, b);
    case '.': return concatSeq(a, b);
    default: throw std::runtime_error("Unknown operator");
    }
}

Node* BSTListStructure::insert(Node* node, int value)
{
    if (!node)
        return new Node(value);
    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);

    return node;
}

Node* BSTListStructure::find(Node* node, int value) const
{
    if (!node || node->value == value)
        return node;
    if (value < node->value)
        return find(node->left, value);
    return find(node->right, value);
}

void BSTListStructure::printTreeHelper(Node* node, int indent) const
{
    if (!node)
        return;
    printTreeHelper(node->right, indent + 4);

    std::cout << std::string(indent, ' ') << node->value << '\n';

    printTreeHelper(node->left, indent + 4);
}

void BSTListStructure::clear(Node* node)
{
    if (!node)
        return;
    clear(node->left);
    clear(node->right);

    delete node;
}

void BSTListStructure::refreshSequence()
{
    sequence.clear();
    std::vector<Node*> stack;
    Node* current = root;
    while (current || !stack.empty())
    {
        while (current)
        {
            stack.push_back(current);
            current = current->left;
        }

        current = stack.back(); stack.pop_back();
        sequence.push_back(current);
        current = current->right;
    }
}

void BSTListStructure::copyTree(const BSTListStructure& other)
{
    std::set<int> values;

    for (auto node : other.sequence)
        if (node)
            values.insert(node->value);

    for (int v : values)
        insertUnique(v);
}