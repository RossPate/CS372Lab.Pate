//
// File: FinalExam_P1.cpp
// Author: Ross Pate
// Purpose: Standalone functions to count nodes, internal nodes, and compute external path length in a binary tree
// using the Tree class from lecture.
//

#include <iostream>
#include "Tree.hpp"

template <typename T>
int countNodes(const Tree<T>& tree) {
    if (tree.isEmpty())
        return 0;
    return 1 + countNodes(tree.left()) + countNodes(tree.right());
}

template <typename T>
int countInternalNodes(const Tree<T>& tree) {
    if (tree.isEmpty() || (tree.left().isEmpty() && tree.right().isEmpty()))
        return 0;
    return 1 + countInternalNodes(tree.left()) + countInternalNodes(tree.right());
}

template <typename T>
void computeExternalPathLength(const Tree<T>& tree, int depth, int& sum) {
    if (tree.isEmpty())
        return;

    if (tree.left().isEmpty() && tree.right().isEmpty()) {
        sum += depth;
    }
    else {
        computeExternalPathLength(tree.left(), depth + 1, sum);
        computeExternalPathLength(tree.right(), depth + 1, sum);
    }
}

// Used ChatGpt to generate "test" numbers for the functions
int main() {
    Tree<int> myTree = { 10, 5, 15, 3, 7, 12, 18 };

    std::cout << "Total number of nodes: " << countNodes(myTree) << std::endl;
    std::cout << "Number of internal nodes: " << countInternalNodes(myTree) << std::endl;

    int externalPathLength = 0;
    computeExternalPathLength(myTree, 0, externalPathLength);
    std::cout << "External path length: " << externalPathLength << std::endl;

    return 0;
}
