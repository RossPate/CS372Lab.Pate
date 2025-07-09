//
// File:   kevinBaconSocialGraphTest_Asg07.cpp
// Author: Ross Pate
// Purpose:
// Test a social graph pertaining to Kevin Bacon

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include "Graph.hpp"
#include "AdjListGraph.hpp"

AdjListGraph<std::string> buildSocialGraph();
bool findConnectionPath(
    AdjListGraph<std::string>& graph,
    const std::string& from,
    const std::string& to,
    std::vector<std::string>& path);

TEST(SocialGraphTest, PathToKevinBacon) {
    auto graph = buildSocialGraph();
    std::vector<std::string> path;
    bool connected = findConnectionPath(graph, "You", "Kevin Bacon", path);

    EXPECT_TRUE(connected);
    ASSERT_FALSE(path.empty());
    EXPECT_EQ(path.front(), "You");
    EXPECT_EQ(path.back(), "Kevin Bacon");
    std::cout << "Path: ";
    for (const auto& name : path) {
        if (name == "Kevin Bacon") {
            std::cout << name;
        }
        else {
            std::cout << name << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Kevin Bacon number: " << (path.size() - 1) << std::endl;
}

