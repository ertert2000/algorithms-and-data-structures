#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>

struct Node 
{
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int v) : value(v) {}
};

class BSTListStructure 
{
public:
    Node* root = nullptr;
    std::list<Node*> sequence;

    BSTListStructure() = default;
    ~BSTListStructure() { clear(root); }

    BSTListStructure(const BSTListStructure&) = delete;
    BSTListStructure& operator=(const BSTListStructure&) = delete;

    BSTListStructure(BSTListStructure&& other) noexcept 
    {
        root = other.root;
        sequence = std::move(other.sequence);
        other.root = nullptr;
    }

    BSTListStructure& operator=(BSTListStructure&& other) noexcept 
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

    void insertUnique(int value) 
    {
        if (!exists(value)) root = insert(root, value);
    }

    void addToSequence(int value) 
    {
        Node* found = find(root, value);
        if (found) sequence.push_back(found);
    }

    void printTree() const 
    {
        printTreeHelper(root, 0);
    }

    void printSequence() const 
    {
        for (auto node : sequence) 
        {
            if (node) std::cout << node->value << ' ';
            else std::cout << "";
        }
        std::cout << '\n';
    }

    bool exists(int value) const 
    {
        return find(root, value) != nullptr;
    }

    static BSTListStructure intersect(const BSTListStructure& a, const BSTListStructure& b) 
    {
        BSTListStructure result;
        for (auto node : a.sequence)
            if (node && b.exists(node->value)) result.insertUnique(node->value);
        result.refreshSequence();
        return result;
    }

    static BSTListStructure unify(const BSTListStructure& a, const BSTListStructure& b) 
    {
        BSTListStructure result;
        for (auto node : a.sequence)
            if (node) result.insertUnique(node->value);
        for (auto node : b.sequence)
            if (node) result.insertUnique(node->value);
        result.refreshSequence();
        return result;
    }

    static BSTListStructure xorSet(const BSTListStructure& a, const BSTListStructure& b) 
    {
        BSTListStructure result;
        std::set<int> onlyA, onlyB;
        for (auto node : a.sequence)
            if (node && !b.exists(node->value)) onlyA.insert(node->value);
        for (auto node : b.sequence)
            if (node && !a.exists(node->value)) onlyB.insert(node->value);
        for (int v : onlyA) result.insertUnique(v);
        for (int v : onlyB) result.insertUnique(v);
        result.refreshSequence();
        return result;
    }

    static BSTListStructure mergeSeq(const BSTListStructure& a, const BSTListStructure& b) 
    {
        BSTListStructure result;
        result.copyTreePreserveOrder(a);
        for (auto node : a.sequence) result.sequence.push_back(result.find(result.root, node->value));
        for (auto node : b.sequence) result.sequence.push_back(result.find(result.root, node->value));
        return result;
    }

    static BSTListStructure exclSeq(const BSTListStructure& a, const BSTListStructure& b) 
    {
        BSTListStructure result;
        result.copyTreePreserveOrder(a);
        for (auto node : a.sequence)
            if (node && std::none_of(b.sequence.begin(), b.sequence.end(), [&](Node* n) { return n && n->value == node->value; }))
                result.sequence.push_back(result.find(result.root, node->value));
        return result;
    }

    static BSTListStructure concatSeq(const BSTListStructure& a, const BSTListStructure& b) 
    {
        BSTListStructure result;
        result.copyTreePreserveOrder(a);
        for (auto node : a.sequence) result.sequence.push_back(result.find(result.root, node->value));
        for (auto node : b.sequence) result.sequence.push_back(result.find(result.root, node->value));
        return result;
    }

    static BSTListStructure generate(int count, int universe) 
    {
        BSTListStructure obj;
        std::set<int> used;
        while (obj.sequence.size() < static_cast<size_t>(count)) 
        {
            int v = rand() % universe;
            if (!obj.exists(v)) 
            {
                obj.insertUnique(v);
                Node* node = obj.find(obj.root, v);
                if (node) obj.sequence.push_back(node);
            }
        }
        return obj;
    }

    static BSTListStructure simpleEval(char op, const BSTListStructure& a, const BSTListStructure& b) 
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

    static std::pair<BSTListStructure, BSTListStructure> prepareIntersection(int count, int universe, int common) {
        BSTListStructure A, B;
        std::set<int> used;

        while (A.sequence.size() < static_cast<size_t>(common)) {
            int val = rand() % universe;
            if (used.insert(val).second) {
                A.insertUnique(val);
                B.insertUnique(val);
                Node* na = A.find(A.root, val);
                Node* nb = B.find(B.root, val);
                if (na) A.sequence.push_back(na);
                if (nb) B.sequence.push_back(nb);
            }
        }
        while (A.sequence.size() < static_cast<size_t>(count)) {
            int val = rand() % universe;
            if (used.insert(val).second) {
                A.insertUnique(val);
                Node* na = A.find(A.root, val);
                if (na) A.sequence.push_back(na);
            }
        }

        while (B.sequence.size() < static_cast<size_t>(count)) {
            int val = rand() % universe;
            if (used.insert(val).second) {
                B.insertUnique(val);
                Node* nb = B.find(B.root, val);
                if (nb) B.sequence.push_back(nb);
            }
        }

        return std::make_pair(std::move(A), std::move(B));
    }


    size_t getPower() const 
    {
        return sequence.size();
    }

private:
    Node* insert(Node* node, int value) 
    {
        if (!node) return new Node(value);
        if (value < node->value) node->left = insert(node->left, value);
        else if (value > node->value) node->right = insert(node->right, value);
        return node;
    }

    Node* find(Node* node, int value) const 
    {
        if (!node || node->value == value) return node;
        if (value < node->value) return find(node->left, value);
        return find(node->right, value);
    }

    void printTreeHelper(Node* node, int indent) const 
    {
        if (!node) return;
        printTreeHelper(node->right, indent + 4);
        std::cout << std::string(indent, ' ') << node->value << '\n';
        printTreeHelper(node->left, indent + 4);
    }

    void clear(Node* node) 
    {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void refreshSequence() 
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

    void copyTreePreserveOrder(const BSTListStructure& other) 
    {
        clear(root);
        for (auto node : other.sequence)
            if (node) insertUnique(node->value);
    }
};
