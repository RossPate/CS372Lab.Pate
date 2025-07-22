//
//  File:   AdjMatrixGraph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Implementation of the adjacency list implementation of the graph ADT
//
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Graph.hpp"
using namespace std;
template <class N>
class AdjMatrixGraph: public Graph<N>  {
private:
	std::vector<N> nodes;
    const static int maxSize = 10;
    short adjMatrix[maxSize][maxSize] = {};
    int numNodes = 0;
    int findNodeInMatrix(N x){
        for (int j=0; j < numNodes; ++j)
        {
            if (x == nodes[j])
            {
                return j;
            }
        }
        return -1;
    }
public:
    // Default constuctor, create empty
	AdjMatrixGraph() = default;

    // Add the nodes in the list to graph
    AdjMatrixGraph(vector<N> newNodes, vector<pair<N,N>> newEdges)
    {
        for (typename vector<N>::const_iterator it = newNodes.begin();
             it < newNodes.end();
             ++it)
        {
			numNodes++;
            nodes.push_back(*it);
        }
        for (typename vector<pair<N,N>>::const_iterator it = newEdges.begin();
             it < newEdges.end();
             ++it)
        {
            pair<N,N> edge = *it;
            int sourceIndex = findNodeInMatrix(edge.first);
            int destIndex = findNodeInMatrix(edge.second);
            if (sourceIndex != -1)
            {
                if (destIndex != -1)
                {
                    adjMatrix[sourceIndex][destIndex] = 1;
                }
            }
        }
    }

    // Clean up behind ourselves
    virtual ~AdjMatrixGraph() = default;
    
    virtual bool adjacent(N x, N y)
    {
        bool result = false;
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            short xy = adjMatrix[xIndex][yIndex];
            if (xy == 1) {result = true; };
        }
        return(result);
    }

    virtual vector<N> & neighbors(N x)
    {
        vector<N> * v = new vector<N>();
        int xIndex = findNodeInMatrix(x);
        if (xIndex != -1)
        {
            for (int i=0; i < numNodes; ++i) {
                if (adjMatrix[xIndex][i] > 0) {
                    v->push_back(nodes[i]);
                }
            }
        }
        return *v;
    }
    virtual void addNode(N node)
    {
        nodes.push_back(node);
        numNodes++;

    }
    virtual void addEdge(N x, N y){
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            adjMatrix[xIndex][yIndex] = 1;
        }
    }
    virtual void deleteEdge(N x, N y)
    {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        adjMatrix[xIndex][yIndex] = 0;
    }

    // Traversals
    void dfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;

         for (int i = 0; i < numNodes; ++i){
            visited[nodes[i]] = false;
        }
        stack<N> s;
        s.push(startNode);
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec ) {
                if (!visited[neighbor]) { s.push(neighbor); }
            }
        }
    }
    
    void bfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        for (int i = 0; i < numNodes; ++i){
            visited[nodes[i]]= false;
        }
        queue<N> q;
        q.push(startNode);
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec) {
                if (!visited[neighbor]) { q.push(neighbor); }
            }
        }
    }};
