#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Graph {
    struct Flight {
        int target;   // Target Airport
        string code;  // AirlineCode
    };

    struct Airport {
        string code; // Airport code
        list<Flight> connected; // The list of outgoing flights (to connected airports)
        bool visited;   // As the airport been visited on a search?
        int distance;   // Distance from source airport on a search
    };

    int n;              // Graph size (airports are numbered from 1 to n)
    vector<Airport> airports; // The list of airports being represented

public:
    // Constructor: nr airports
    Graph(int airports);

    // Add Flight from source to target
    void addFlight(int src, int trgt, string code);

    // Breadth-First Search
    void bfs(int v);

};

#endif