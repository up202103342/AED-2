#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

//---------------------------------

struct hFunc {
    int operator() (const string& ap) const {
        unsigned long hash = 0;
        for(int i = 0; i < ap.length(); i++) {
            hash = (hash * 37) + int(ap[i]);
        }
        return hash % 3023;
    }
};

struct eqFunc {
    bool operator() (const string& apCode1, const string& apCode2) const {
        return apCode1==apCode2 ;
    }
};

typedef unordered_map<string, Airport, hFunc, eqFunc> hTable;

Airport searchAp(hTable &hT, string const& apCode) {
    return hT[apCode];
}

//---------------------------------

void readAirports(hTable& hT1, Graph g) {
    int n;
    ifstream infile("data/airports.csv");
    string line;
    bool first = true;
    while (getline(infile, line, ',')) {
        if (first) { first = false;}
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
                else if (line[i] == ' ') {
                    line[i] = '_';
                }
            }
            istringstream iss(line);
            string Code,Name,City,Country;
            float Latitude,Longitude;
            iss >> Code >> Name >> City >> Country >> Latitude >> Longitude;
            n++;
            Airport ap = Airport(n, Code, Name, City, Country, Latitude, Longitude);
            hT1[ap.getCode()] = ap;
        }
    }
    g = new Graph(n);
    return hT1;
}

void readAirlines() {
    ifstream infile("data/airlines.csv");
    string line;
    bool first = true;
    while (getline(infile, line, ',')) {
        if (first) { first = false;}
        else {
            istringstream iss(line);
            string Code,Name,Callsign,Country;
            iss >> Code >> Name >> Callsign >> Country;

            Airline al = Airline(Code, Name, Callsign, Country);
        }
    }
}

void readFlights(Graph g, hTable hT) {
    ifstream infile("data/flights.csv");
    string line;
    bool first = true;
    while (getline(infile, line, ',')) {
        if (first) { first = false;}
        else {
            istringstream iss(line);
            string Source,Target,Airline;
            iss >> Source >> Target >> Airline;

            int src = ;
            int tgt = ;
            g.addFlight(src, tgt, Airline);
        }
    }
}

Airport getClosest(Airport ap, Graph g, hTable hT) {
    int n = g.getClosestAirport(ap.getCode());
    return hT[n];
}





int main() {
    hTable hT1;
    Graph g;
    readAirports(hT1, g);
    if(hT1.empty()) return 1;
    Airport ap = searchAp(hT1, "JFK");
    cout << ap.getName();
    return 0;
}
