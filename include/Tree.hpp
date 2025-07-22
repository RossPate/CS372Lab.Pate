//
// File:    Tree.h
// Author:  Adam.Lewis@athens.edu
// Purpose:
// Use C++ templates, STL classes and functions, and smart pointers to
// implement a binary search tree.
//
// A binary search tree is defined as being either empty, or a 3-tuple
// (left.subtree, value, right.subtree) where left.subtree is a binary search
// tree that only contains values less than our value and right.subtree is a
// binary search tree that only contains values larger than our value.
//
#pragma once

#include <queue>
#include <memory>
#include <functional>
#include <cassert>
using namespace std;

template<class T>
class Tree
{
    // The inner struct Node represents one node of the tree.  This defines the
    // underlying structure implied by the mathematical definition of the Tree
    // ADT
    //
    struct Node
    {
        Node(std::shared_ptr<const Node> const& lft,
            T val,
            std::shared_ptr<const Node> const& rgt,
            std::weak_ptr<const Node> const& parent = std::weak_ptr<const Node>())
            : _lft(lft), _val(val), _rgt(rgt), _parent(parent)
        {
        }

        std::shared_ptr<const Node> _lft;
        T _val;
        std::shared_ptr<const Node> _rgt;
        std::weak_ptr<const Node> _parent;
    };

    //
    // And this private constructor defines how we keep track of the root of the
    // tree while not exposing that information to clients of this class.
    //
    explicit Tree(std::shared_ptr<const Node> const& node)
        : _root(node) {
    }

    unsigned int numberOfNodes = 0;
public:
    //
    // The first two public constructors provide the protocol for creating a
    // Tree per the mathematical definition of the Tree ADT.
    //
    Tree() {}

    Tree(Tree const& lft, T val, Tree const& rgt)
    {
        // Create the new node with parent nullptr (root node)
        auto newNode = std::make_shared<Node>(lft._root, val, rgt._root, std::weak_ptr<const Node>());
        // Set parent pointers for left and right children if they exist
        if (lft._root) {
            // Create a copy of left node with parent set to newNode
            auto leftNode = std::make_shared<Node>(*lft._root);
            const_cast<std::weak_ptr<const Node>&>(leftNode->_parent) = newNode;
            newNode->_lft = leftNode;
        }
        if (rgt._root) {
            auto rightNode = std::make_shared<Node>(*rgt._root);
            const_cast<std::weak_ptr<const Node>&>(rightNode->_parent) = newNode;
            newNode->_rgt = rightNode;
        }
        _root = newNode;
        assert(lft.isEmpty() || lft.root() < val);
        assert(rgt.isEmpty() || val < rgt.root());
    }

    //
    // We add an additional constructor that we use to construct a Tree from
    // an initializer list.
    //
    Tree(std::initializer_list<T> init) {
        Tree t;
        for (T v : init) {
            t = t.insert(v);
        }
        _root = t._root;
    }

    //
    // The next portion of the protocol allows the client to query the state
    // of the Tree.   Again, note how we avoid exposing the state to the client.
    //
    bool isEmpty() const { return !_root; }

    size_t size() { return numberOfNodes; }

    T root() const {
        assert(!isEmpty());
        return _root->_val;
    }

    Tree left() const {
        assert(!isEmpty());
        return Tree(_root->_lft);
    }

    Tree right() const {
        assert(!isEmpty());
        return Tree(_root->_rgt);
    }

    //
    // Now we manipulate the tree.
    // Note insert operates... we don't try to "fix" an existing treee.
    // Rather we build a new tree, inserting the new value at the correct point.
    //
    // Note also the implicit assumption about the template class... it must
    // support the comparison operator, or mathematically, must be partially
    // ordered.
    //
    Tree insert(T x) {
        numberOfNodes++;
        if (isEmpty()) {
            // New root node, parent is nullptr
            return Tree(std::make_shared<Node>(nullptr, x, nullptr, std::weak_ptr<const Node>()));
        }
        T y = root();
        if (x < y) {
            Tree newLeft = left().insert(x);
            auto newNode = std::make_shared<Node>(newLeft._root, y, right()._root, std::weak_ptr<const Node>());
            if (newLeft._root)
                const_cast<std::weak_ptr<const Node>&>(newLeft._root->_parent) = newNode;
            if (right()._root)
                const_cast<std::weak_ptr<const Node>&>(right()._root->_parent) = newNode;
            return Tree(newNode);
        }
        else if (y < x) {
            Tree newRight = right().insert(x);
            auto newNode = std::make_shared<Node>(left()._root, y, newRight._root, std::weak_ptr<const Node>());
            if (left()._root)
                const_cast<std::weak_ptr<const Node>&>(left()._root->_parent) = newNode;
            if (newRight._root)
                const_cast<std::weak_ptr<const Node>&>(newRight._root->_parent) = newNode;
            return Tree(newNode);
        }
        else {
            return *this; // no duplicates
        }
    }

    bool member(T x) const {
        if (isEmpty())
            return false;
        T y = root();
        if (x < y)
            return left().member(x);
        else if (y < x)
            return right().member(x);
        else
            return true;
    }

    bool find(T x, T& foundValue) const {
        if (isEmpty())
            return false;
        T y = root();
        if (x < y)
            return left().find(x);
        else if (y < x)
            return right().find(x);
        else {
            foundValue = y;
            return true;
        }
    }

    //
    // For each of traversal functions, we assume that the parameter is a
    // function pointer, object, or lambda expression that returns void and is
    // passed an object of type T.
    //
    void preorder(std::function<void(T)> visit) const {
        if (isEmpty())
            return;
        T contents = root();
        visit(contents);
        left().preorder(visit);
        right().preorder(visit);
    }

    void inorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().inorder(visit);
        T contents = root();
        visit(contents);
        right().inorder(visit);
    }

    void postorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().postorder(visit);
        right().postorder(visit);
        T contents = root();
        visit(contents);
    }

private:
    std::shared_ptr<const Node> _root;
};

// Stand-alone level-order traversal function
template <typename T>
void levelOrderTraversal(const Tree<T>& tree, std::function<void(T)> visit) {
    if (tree.isEmpty()) return;

    std::queue<Tree<T>> nodeQueue;
    nodeQueue.push(tree);

    while (!nodeQueue.empty()) {
        Tree<T> current = nodeQueue.front();
        nodeQueue.pop();

        visit(current.root());

        if (!current.left().isEmpty())
            nodeQueue.push(current.left());

        if (!current.right().isEmpty())
            nodeQueue.push(current.right());
    }
}
// Stand alone function prune to show recursive pruning logic
template <typename T>
Tree<T> prune(const Tree<T>& tree) {
    if (tree.isEmpty()) return Tree<T>();

    // If both left and right are empty, it's a leaf — remove it
    if (tree.left().isEmpty() && tree.right().isEmpty()) {
        return Tree<T>();
    }

    // Recursively prune left and right
    Tree<T> prunedLeft = prune(tree.left());
    Tree<T> prunedRight = prune(tree.right());

    // Return new tree with pruned children
    return Tree<T>(prunedLeft, tree.root(), prunedRight);
}