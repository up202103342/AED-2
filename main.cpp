#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

Graph readAirports(hTable& hT1) {
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
    Graph g(n);
    return g;
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

            int src = searchAp(hT, Source).getID();
            int tgt = searchAp(hT, Target).getID();
            g.addFlight(src, tgt, Airline);
        }
    }
}

Airport getClosest(Airport ap, Graph g, hTable hT) {
    int n = g.getClosestAirport(ap.getId(), hT);
    return hT[g.airportIDToCode(n)];
}





int main() {
    hTable hT1;
    readAirports(hT1);
    if(hT1.empty()) return 1;
    Airport ap = searchAp(hT1, "JFK");
    cout << ap.getName();
    return 0;
}
