#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "hashTable.cpp"

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
    // Default constructor
    Graph();
    // Constructor: nr airports
    Graph(int airports);

    // Add Flight from source to target
    void addFlight(int src, int trgt, string code);

    // Breadth-First Search
    void bfs(int v);

    list<int> getConnectedAirports(int n);
    int getClosestAirport(int n, hTable hT);
    bool flightInAirlines(string code, list<string> airlines);
    int lastStop(int src, int tgt, list<string> airlines);
    list<int> getShortestTrip(int src, int tgt, list<string> airlines);
    int flightsFromAirport(int n);
    int airlinesFlyingFromAirport(int n);
    int citiesFlownToFromAirport(int n, hTable hT);
    int countriesFlownToFromAirport(int n, hTable hT);
    int numberOfAirportsReachableInNFlights(int src, int n);
    int numberOfCitiesReachableInNFlights(int src, int n, hTable hT);
    int numberOfCountriesReachableInNFlights(int src, int n, hTable hT);
    list<int> getLocalToLocal(int src, int tgt, string city1, string city2, float lg1, float lt1, float lg2, float lt2, hTable hT, list<string> airlines);
    string airportIDToCode(int n);

};

#endif