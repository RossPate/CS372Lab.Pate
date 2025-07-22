//
//  File:   Graph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Abstract base class (pure virtual class) for Graphs
//
#pragma once
#include <vector>
#include <utility>
#include <functional>
template <class N>
class Graph {
public:
    // Default constuctor, create empty
    Graph() = default;
    Graph(std::vector<N> nodes, std::vector<std::pair<N, N>> edges) {};
    virtual ~Graph() = default;
    
    virtual bool adjacent(N x, N y) = 0;
    virtual std::vector<N> &neighbors(N x) = 0;
    virtual void addNode(N x) = 0;
    virtual void addEdge(N x, N y) = 0;
    virtual void deleteEdge(N x, N y) = 0;
    // Traversals
    virtual void dfs(N startNode, std::function<void(N)> visit) = 0;
    virtual void bfs(N startNode, std::function<void(N)> visit) = 0;
};

