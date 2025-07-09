//
// File:   kevinBaconSocialGraph_Asg07.cpp
// Author: Ross Pate
// Purpose:
// Show a social graph pertaining to Kevin Bacon

#include <vector>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
#include "Graph.hpp"
#include "AdjListGraph.hpp"

AdjListGraph<std::string> buildSocialGraph() {
    AdjListGraph<std::string> graph;
    std::vector<std::string> people = {
        "You", "Kevin Bacon", "Alice", "Bob", "Carol", "Dave", "Eve", "Frank", "Grace", "Heidi",
        "Ivan", "Judy", "Mallory", "Niaj", "Olivia", "Peggy", "Quentin", "Rupert", "Sybil", "Trent"
    };
    for (const auto& person : people) {
        graph.addNode(person);
    }
    graph.addEdge("You", "Alice");
    graph.addEdge("Alice", "Bob");
    graph.addEdge("Bob", "Carol");
    graph.addEdge("Carol", "Kevin Bacon");
    graph.addEdge("You", "Eve");
    graph.addEdge("Eve", "Frank");
    graph.addEdge("Frank", "Kevin Bacon");
    graph.addEdge("You", "Grace");
    graph.addEdge("Grace", "Heidi");
    graph.addEdge("Heidi", "Kevin Bacon");
    graph.addEdge("Kevin Bacon", "Ivan");
    graph.addEdge("Ivan", "Judy");
    graph.addEdge("Judy", "Mallory");
    graph.addEdge("Mallory", "Niaj");
    graph.addEdge("Niaj", "Olivia");
    graph.addEdge("Olivia", "Peggy");
    graph.addEdge("Peggy", "Quentin");
    graph.addEdge("Quentin", "Rupert");
    graph.addEdge("Rupert", "Sybil");
    graph.addEdge("Sybil", "Kevin Bacon");
    return graph;
}

bool findConnectionPath(
    AdjListGraph<std::string>& graph,
    const std::string& from,
    const std::string& to,
    std::vector<std::string>& path)
{
    std::map<std::string, std::string> prev;
    std::map<std::string, bool> visited;
    std::queue<std::string> q;

    q.push(from);
    visited[from] = true;

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        if (current == to) {
            path.clear();
            for (std::string at = to; !at.empty(); at = prev[at]) {
                path.push_back(at);
                if (at == from) break;
            }
            std::reverse(path.begin(), path.end());
            return true;
        }

        std::vector<std::string>& neighRef = graph.neighbors(current);
        std::vector<std::string> neighbors = neighRef;
        delete& neighRef;

        for (const auto& neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                prev[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    path.clear();
    return false;
}
