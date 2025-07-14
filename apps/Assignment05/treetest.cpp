//
// File:   treetest.cpp
// Author: Your Glorious Instructor
// Purpose:
// Provide unit tests for our Tree class
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <random>
#include <list>
#include "Tree.hpp"

// Test fixtures manage the state of the test. 
// Test fixtures are subclass of the ::testing::Test class, with
// all contents set as protected.   As we are using member 
// variables not allocated on the heap, no need to do any
// special setup or teardown.  Do need to use the TEST_F() macro
// rather TEST()

Tree<int> aTree{ 45,74,28,32,44, 100 };
std::list<int> resultList;
void printIt(int thing) { std::cout << thing << " "; }
void addToResult(int thing) { resultList.push_back(thing); }

template <typename Iterable>
void printAny(Iterable aContainer) {
	for (auto aThing : aContainer) {
		std::cout << aThing << " ";
	}
	std::cout << std::endl;
}
// Test: Verify that a preorder traversal happens in correct order
// Precondition: A BST has been created
// Postcondition: A list is created that has the correct preorder walk
//                of the tree.
TEST(TreeFixture, PreorderTraversal) {
	aTree.preorder(addToResult);
	printAny(resultList);
	aTree.preorder(printIt);
	resultList.clear();
}

// Test: Verify that a preorder traversal happens in correct order
// Precondition: A BST has been created
// Postcondition: A list is created that has the correct preorder walk
//                of the tree.
TEST(TreeFixture, PostorderTraversal) {
	aTree.postorder(addToResult);
	printAny(resultList);
	aTree.postorder(printIt);
	resultList.clear();
}

// Test: Verify that a preorder traversal happens in correct order
// Precondition: A BST has been created
// Postcondition: A list is created that has the correct preorder walk
//                of the tree.
TEST(TreeFixture, InorderTraversal) {
	aTree.inorder(addToResult);
	printAny(resultList);
	aTree.inorder(printIt);
	resultList.clear();
}


