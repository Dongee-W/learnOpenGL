#pragma once
// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
#include<iostream>
#include <list>
#include <vector>

#include "../opengl/Model.h"

using namespace std;

// This class represents a directed graph using
// adjacency list representation
class SceneGraph
{
    int V;    // No. of vertices

    // Pointer to an array containing adjacency
    // lists
    list<int>* adj;
public:
    SceneGraph(int V);  // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);

    // prints BFS traversal from a given source s
    void BFS(int s);
    vector<vector<int>> bfsHistory(int s);
};

struct SceneNode {
    Model* model;
    glm::mat4 modelMatrix;
};
