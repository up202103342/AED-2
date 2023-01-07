#include "Graph.h"
#include <queue>

static float haversine(float lat1, float lon1,
                       float lat2, float lon2)
{
    // distance between latitudes
    // and longitudes
    float dLat = (lat2 - lat1) *
                 M_PI / 180.0;
    float dLon = (lon2 - lon1) *
                 M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    float a = pow(sin(dLat / 2), 2) +
              pow(sin(dLon / 2), 2) *
              cos(lat1) * cos(lat2);
    float rad = 6371;
    float c = 2 * asin(sqrt(a));
    return rad * c;
}

// Constructor: nr airports and direction (default: undirected)
Graph::Graph(int num) : n(num), airports(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addFlight(int src, int trgt, string code) {
    if (src<1 || src>n || trgt<1 || trgt>n) return;
    airports[src].connected.push_back({trgt, code});
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
                airports[w].visited = true;
                airports[w].distance=airports[u].distance+1;
            }
        }
    }
}

list<int> Graph::getConnectedAirports(int n){
    list<int> aps;
    for(auto a : airports[n].connected) aps.push_back(a.target);
    return aps;
}


void Graph::getClosest(int n){
    int d=INT64_MAX;
    int res;
    for (int x : airports[n].connected){
        if (d > haversine(airports[n].getLatitude(), airports[n].getLongitude(), airports[x].getLatitude(), airports[x].getLongitude())) {
            d = haversine(airports[n].getLatitude(), airports[n].getLongitude(), airports[x].getLatitude(), airports[x].getLongitude());
            res = x;
        }
    }
    return x;
}

bool flightInAirlines(string code, list<string> airlines) {
    for (string s : airlines) {
        if (s == code) { return true; }
    }
    return false;
}

int lastStop(int src, int tgt, list<string> airlines) {
    bool all_airlines = false;
    if (airlines.size() == 0) all_airlines = true;
    for (int i=1; i<=n; i++) airports[i].visited = false;
    queue<int> q;
    q.push(src);
    airports[src].distance=0;
    airports[src].visited = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : airports[u].connected) {
            if ((!all_airlines && flightInAirlines(e.code, airlines)) || all_airlines) {
                int w = e.target;
                if (!airports[w].visited) {
                    q.push(w);
                    airports[w].visited = true;
                    airports[w].distance = airports[u].distance + 1;
                    if (w == tgt) {
                        return u;
                    }
                }
            }
        }
    }
    return -1;
}

list<int> Graph::getShortestTrip(int src, int tgt, list<string> airlines) {
    list<int> res;
    if (lastStop(src, tgt, airlines) == -1) { return res;}
    res.push_back(tgt);
    while (*(res.begin()) != src) {
        int stop = lastStop(src, *(res.begin()), airlines);
        res.push_front(stop);
    }
    return res;
}

int Graph::flightsFromAirport(int n) {
    return airports[n].connected.size();
}

int Graph::airlinesFlyingFromAirport(int n) {
    list<string> airlines;
    for (auto u : airports[n].connected) {
        if (!flightInAirlines(u.code, airlines)) {
            airlines.push_back(u.code);
        }
    }
    return airlines.size();
}

int citiesFlownToFromAirport(int n);
int countriesFlownToFromAirport(int n);
int numberOfAirportsReachableInNFLights(int src, int n) {
    bfs(src);
    int res = 0;
    for (auto a : airports) {
        if (a.visited) {
            if (a.distance <= n) {
                res++;
            }
        }
    }
    return res;
}
int numberOfCitiesReachableInNFLights(int src, int n);
int numberOfCountriesReachableInNFLights(int src, int n);

