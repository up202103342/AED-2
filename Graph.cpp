#include "graph.h"
#include <queue>

// Constructor: nr airports and direction (default: undirected)
Graph::Graph(int num) : n(num), airports(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addFlight(int src, int trgt, string code) {
    if (src<1 || src>n || trgt<1 || trgt>n) return;
    airports[src].connected.push_back({trgt, code});
    airports[trgt].connected.push_back({src, code});
}


// Breadth-First Search
void Graph::bfs(int v) {
    for (int i=1; i<=n; i++) airports[i].visited = false;
    queue<int> q; // queue of unvisited airports
    q.push(v);
    airports[v].distance=0;
    airports[v].visited = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : airports[u].connected) {
            int w = e.target;
            if (!airports[w].visited) {
                q.push(w);
                airports].visited = true;
                airports[w].distance=airports[u].distance+1;
            }
        }
    }
} 