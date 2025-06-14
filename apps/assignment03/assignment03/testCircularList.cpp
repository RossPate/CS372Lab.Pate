// I had to do quite a bit of googling to get this to work, but it does not quite work the way I would like still.
#include <gtest/gtest.h>
#include "CircularList.h"

class TestCircularList : public ::testing::Test {
protected:
    CircularList<int> cl;

    void SetUp() override {
        cl.push_back(1);
        cl.push_back(2);
        cl.push_back(3);
    }
};

TEST_F(TestCircularList, TestPushBack) {
    // Testing memory / exception issues. Not sure why exception gets thrown
    std::cout << "Tail Node Address: " << cl.getTail() << std::endl;
    std::cout << "Back Value Before Assertion: " << cl.back() << std::endl;
    cl.pop_back();
    cl.push_back(3);
    std::cout << "After re-push_back: " << cl.back() << std::endl;
    EXPECT_EQ(cl.back(), 3);
}

TEST_F(TestCircularList, TestPushFront) {
    cl.push_front(0);
    EXPECT_EQ(cl.front(), 0);
}

TEST_F(TestCircularList, TestCircularTraversal) {
    std::vector<int> collected;
    cl.traverse([&collected](int data) {
        collected.push_back(data);
        }, cl.getHead());

    EXPECT_EQ(collected.size(), cl.size());
    EXPECT_EQ(collected[0], 1);
    EXPECT_EQ(collected[1], 2);
    EXPECT_EQ(collected[2], 3);
}

TEST_F(TestCircularList, TestPopBack) {
    cl.pop_back();
    EXPECT_EQ(cl.back(), 2);
}

TEST_F(TestCircularList, TestPopFront) {
    cl.pop_front();
    EXPECT_EQ(cl.front(), 2);
}

TEST_F(TestCircularList, TestEmptyListBehavior) {
    CircularList<int> emptyList;
    EXPECT_TRUE(emptyList.empty());
}