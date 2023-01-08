#include "Graph.h"
#include <queue>
#include "cmath"

static float haversine(float lat1, float lon1,
                       float lat2, float lon2)
{
    // distance between latitudesS
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
// Default constructor
Graph::Graph() {}

// Constructor: nr airports and direction (default: undirected)
Graph::Graph(int num) : n(num), airports(num+1) {
}

string Graph::airportIDToCode(int n) {
    return airports[n].code;
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


int Graph::getClosestAirport(int n, hTable hT) {
    int d=INT64_MAX;
    int res;
    auto src = searchAp(hT, airports[n].code);
    for (Flight x : airports[n].connected){
        auto ap = searchAp(hT, airports[x.target].code);
        if (d > haversine(src.getLatitude(), src.getLongitude(), ap.getLatitude(), ap.getLongitude())) {
            d = haversine(src.getLatitude(), src.getLongitude(), ap.getLatitude(), ap.getLongitude());
            res = x.target;
        }
    }
    return res;
}

bool Graph::flightInAirlines(string code, list<string> airlines) {
    for (string s : airlines) {
        if (s == code) { return true; }
    }
    return false;
}

int Graph::lastStop(int src, int tgt, list<string> airlines) {
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

list<int> Graph::getLocalToLocal(int src, int tgt, string city1, string city2, float lg1, float lt1, float lg2, float lt2, hTable hT, list<string> airlines) {
    list<int> aps1;
    list<int> aps2;
    if (src == -1) {
        if (lg1 == -1) {
            for (auto ap : hT) {
                if ((ap.second.getLongitude() == lg1) && (ap.second.getLatitude() == lt1)) {
                    aps1.push_back(ap.second.getId());
                    break;
                }
            }
        }
        else {
            for (auto ap : hT) {
                if (ap.second.getCity() == city1) {
                    aps1.push_back(ap.second.getId());
                    break;
                }
            }
            city1 = true;
        }
    }
    else aps1.push_back(src);
    if (tgt == -1) {
        if (lg2 == -1) {
            for (auto ap : hT) {
                if ((ap.second.getLongitude() == lg2) && (ap.second.getLatitude() == lt2)) {
                    aps2.push_back(ap.second.getId());
                    break;
                }
            }
        }
        else {
            for (auto ap : hT) {
                if (ap.second.getCity() == city2) {
                    aps2.push_back(ap.second.getId());
                    break;
                }
            }
            city1 = true;
        }
    }
    else aps2.push_back(tgt);
    int min, s, t;
    min = INT64_MAX;
    for (int i : aps1) {
        for (int j : aps2) {
            if (getShortestTrip(i, j, airlines).size() < min) {
                min = getShortestTrip(i, j, airlines).size();
                s = i; t = j;
            }
        }
    }
    return getShortestTrip(s, t, airlines);
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

int Graph::citiesFlownToFromAirport(int n, hTable hT) {
    list<string> cities;
    for (auto u : airports[n].connected) {
        string city = searchAp(hT, u.code).getCity();
        if (!flightInAirlines(city, cities)) {
            cities.push_back(city);
        }
    }
    return cities.size();
}
int Graph::countriesFlownToFromAirport(int n, hTable hT) {
    list<string> countries;
    for (auto u : airports[n].connected) {
        string country = searchAp(hT, u.code).getCountry();
        if (!flightInAirlines(country, countries)) {
            countries.push_back(country);
        }
    }
    return countries.size();
}
int Graph::numberOfAirportsReachableInNFlights(int src, int n) {
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
int Graph::numberOfCitiesReachableInNFlights(int src, int n, hTable hT) {
    bfs(src);
    list<string> cities;
    for (int i = 1; i <= airports.size(); i++) {
        if (airports[i].visited) {
            if (airports[i].distance <= n) {
                string city = searchAp(hT, airports[i].code).getCity();
                if (!flightInAirlines(city, cities)) {
                    cities.push_back(city);
                }
            }
        }
    }
    return cities.size();
}
int Graph::numberOfCountriesReachableInNFlights(int src, int n, hTable hT) {
    bfs(src);
    list<string> countries;
    for (int i = 1; i <= airports.size(); i++) {
        if (airports[i].visited) {
            if (airports[i].distance <= n) {
                string country = searchAp(hT, airports[i].code).getCountry();
                if (!flightInAirlines(country, countries)) {
                    countries.push_back(country);
                }
            }
        }
    }
    return countries.size();
}

vector<int> Graph::countryStats(string country, hTable hT) {
    vector<int> res;
    list<int> aps;
    list<string> arl;
    int flt = 0;
    for (int i = 1; i <= n; i++) {
        if (hT[airports[i].code].getCountry() == country) {
            aps.push_back(i);
        }
    }
    for (int i : aps) {
        flt += flightsFromAirport(i);
        for (auto f : airports[i].connected) {
            if (!flightInAirlines(f.code, arl)) {
                arl.push_back(f.code);
            }
        }
    }
    res.push_back(aps.size());
    res.push_back(arl.size());
    res.push_back(flt);
    return res;
}

int Graph::airlineDiameter(string airline) {
    int max = 0;
    for (int v = 1; v <= n; v++) {
        for (int i = 1; i <= n; i++) { airports[i].visited = false; airports[i].distance = 0; }
        queue<int> q; // queue of unvisited airports
        q.push(v);
        airports[v].distance = 0;
        airports[v].visited = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto e: airports[u].connected) {
                int w = e.target;
                if ((!airports[w].visited) && (e.code == airline)) {
                    q.push(w);
                    airports[w].visited = true;
                    airports[w].distance = airports[u].distance + 1;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (max < airports[i].distance) {
                max = airports[i].distance;
            }
        }
    }
    return max;
}
vector<int> Graph::airlineStats(string airline, hTable hT) {
    vector<int> res;
    int aps = 0;
    int flt = 0;
    for (int i = 1; i <= n; i++) {
        bool hasAirline = false;
        for (auto f : airports[i].connected) {
            if (f.code == airline) {
                flt += 1;
                if (!hasAirline) {
                    aps += 1;
                    hasAirline = true;
                }
            }
        }
    }
    int diameter = airlineDiameter(airline);
    res.push_back(aps);
    res.push_back(flt);
    res.push_back(diameter);
    return res;
}

bool intInVector(int a, vector<int> v) {
    for (int i : v) {
        if (a == i) return true;
    }
    return false;
}

vector<int> Graph::topKAirportsWithMoreFlights(int k) {
    vector<int> res;
    for (int i = 0; i < k; i++) {
        int max = 0;
        int id = 0;
        for (int j = 1; j <= n; j++) {
            if ((flightsFromAirport(j) > max) && (!intInVector(j, res))) {
                max = flightsFromAirport(j);
                id = j;
            }
        }
        res.push_back(id);
    }
    return res;
}
vector<int> Graph::topKAirportsWithMoreAirlines(int k) {
    vector<int> res;
    for (int i = 0; i < k; i++) {
        int max = 0;
        int id = 0;
        for (int j = 1; j <= n; j++) {
            if ((airlinesFlyingFromAirport(j) > max) && (!intInVector(j, res))) {
                max = airlinesFlyingFromAirport(j);
                id = j;
            }
        }
        res.push_back(id);
    }
    return res;
}