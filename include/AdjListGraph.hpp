//
//  File:   AdjListGraph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Implementation of the adjacency list implementation of the graph ADT
//

#include "Graph.hpp"
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

template <class N>
class AdjListGraph: public Graph<N>  {
private:
    using EdgeList = list<pair<N, N>>;
    map<N, EdgeList > vertexMap;
public:
    // Default constructor, create empty
    AdjListGraph() : Graph<N>() { };
    
    // Get the vertex map from the Graph we're copying
    AdjListGraph(const AdjListGraph& other) : Graph<N>() {
        vertexMap = other.vertexMap;
    }
    
    // Don't forget to overload the assignment operator
    AdjListGraph& operator= (const AdjListGraph &source) {
        vertexMap = source.vertexMap;
        return *this;
    }
    
    // Add the nodes in the list to graph
    AdjListGraph(vector<N> newNodes, vector<pair<N,N>> newEdgeVec) :
        Graph<N>(newNodes, newEdgeVec) {
		EdgeList & newEdgeList = EdgeList();
        std::copy(newEdgeVec.begin(), newEdgeVec.end(), std::back_inserter(newEdgeList));
        for (auto it = newNodes.begin();
             it < newNodes.end();
             ++it)
        {
            N node = *it;
            vertexMap[node] = newEdgeList;
        }
    }
    
    
    // Clean up behind ourselves, we're not doing anything with
    // dynamic memory so can use system provided destructor.
    ~AdjListGraph() = default;
    
    virtual bool adjacent(N x, N y){
        EdgeList edges = vertexMap.at(x);
        pair<N,N> *searchEdge = new pair<N,N>(x,y);
        typename EdgeList::const_iterator begin = edges.begin();
        typename EdgeList::const_iterator end = edges.end();
        auto pos = std::find_if(begin,end,
                                [&](pair<N,N> const &b) {
            bool match =  (b.first == searchEdge->first
                           && b.second == searchEdge->second);
            return match;
        });
        bool match = false;
        if (pos != end) { match = true; }
        return (match);
    }
    
    virtual vector<N> &neighbors(N x) {
        vector<N> *nodes = new vector<N>();
        EdgeList edges = vertexMap.at(x);
        for (typename EdgeList :: const_iterator it = edges.begin(); it != edges.end(); it++) {
            pair<N,N> e = *it;
            nodes->push_back(e.second);
        }
        return *nodes;
    }
    
    virtual void addNode(N node){
        EdgeList * newEdgeList = new EdgeList();
        vertexMap[node] = *newEdgeList;
    }
    
    virtual void addEdge(N x, N y){
        pair<N,N> forwardEdge = make_pair(x,y);
        vertexMap[x].push_back(forwardEdge);

    }
    
    virtual void deleteEdge(N x, N y){
        pair<N,N> forwardEdge = make_pair(x,y);
        vertexMap[x].remove(forwardEdge);
    }
    
    // Traversals
    void dfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        stack<N> s;
        for (auto v : vertexMap) {
            visited[v.first] = false;
        }
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
        for (auto v: vertexMap) {
            visited[v.first] = false;
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
    }
};
