#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_set>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

//---------------------------------

struct hFunc {
    int operator() (const Airport& ap) const {
        unsigned long hash = 0;
        for(int i = 0; i < ap.getCode().length(); i++)
        {
            hash = (hash * 37) + ap.getCode()[i];
        }
        return hash % 3023;
    }
};

struct eqFunc {
    bool operator() (const Airport& ap1, const Airport& ap2) const {
        return ap1.getCode()==ap2.getCode() ;
    }
};

typedef unordered_set<Airport, hFunc,eqFunc> hTable;

//---------------------------------

void readAirports(Graph g) {
    int n;
    ifstream infile("data/airports.csv");
    string line;
    bool first = true;
    while (getline(infile, line, ',')) {
        if (first) { first = false;}
        else {
            istringstream iss(line);
            string Code,Name,City,Country;
            float Latitude,Longitude;
            iss >> Code >> Name >> City >> Country >> Latitude >> Longitude;
            n++;
            Airport ap = Airport(n, Code, Name, City, Country, Latitude, Longitude);
            hTable hT1;
            hT1.insert(ap);
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
    return 0;
}
