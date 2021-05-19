#include "SceneGraph.h"

SceneGraph::SceneGraph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void SceneGraph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v¡¦s list.
}

void SceneGraph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

vector<vector<int>> SceneGraph::bfsHistory(int s) {

    vector<vector<int>> allPath;
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<vector<int>> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    vector<int> history = { s };
    allPath.push_back(history);
    queue.push_back(history);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        history = queue.front();
        s = history.back();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                vector<int> cache = history;
                cache.push_back(*i);
                allPath.push_back(cache);
                queue.push_back(cache);
            }
        }
    }
    return allPath;
}