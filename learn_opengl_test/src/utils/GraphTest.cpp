#include <gtest/gtest.h>

#include "utils/Graph.h"

TEST(Graph, Creation) {
    // Create a graph given in the above diagram
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(1, 7);
    g.addEdge(2, 6);

    cout << "Following is Breadth First Traversal "
        << "(starting from vertex 2) \n";
    auto result = g.bfsHistory(0);
    for (auto& r : result) {
        for (auto& j : r) {
            std::cout << j << ", ";
        }
        std::cout << std::endl;
    }
}
