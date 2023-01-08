#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

Graph readAirports(hTable& hT1) { // O(V * n)
    int n = 0;
    ifstream infile("data/airports.csv");
    string line;
    bool first = true;
    while (getline(infile, line)) {
        if (first) { first = false;}
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ' ') {
                    line[i] = '_';
                }
            }
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }
            istringstream iss(line);
            string Code,Name,City,Country;
            float Latitude,Longitude;
            iss >> Code >> Name >> City >> Country >> Latitude >> Longitude;
            n++;
            for (int i = 0; i < Name.length(); ++i) {
                if (Name[i] == '_') {
                    Name[i] = ' ';
                }
            }
            for (int i = 0; i < City.length(); ++i) {
                if (City[i] == '_') {
                    City[i] = ' ';
                }
            }
            for (int i = 0; i < Country.length(); ++i) {
                if (Country[i] == '_') {
                    Country[i] = ' ';
                }
            }
            Airport ap = Airport(n, Code, Name, City, Country, Latitude, Longitude);
            hT1[ap.getCode()] = ap;
        }
    }
    Graph g(n);
    return g;
}

void readAirlines(vector<Airline> & airlines) { // O(n^2)
    ifstream infile("data/airlines.csv");
    string line;
    bool first = true;
    while (getline(infile, line)) {
        if (first) { first = false;}
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ' ') {
                    line[i] = '_';
                }
            }
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }
            istringstream iss(line);
            string Code,Name,Callsign,Country;
            iss >> Code >> Name >> Callsign >> Country;

            for (int i = 0; i < Name.length(); ++i) {
                if (Name[i] == '_') {
                    Name[i] = ' ';
                }
            }
            for (int i = 0; i < Country.length(); ++i) {
                if (Country[i] == '_') {
                    Country[i] = ' ';
                }
            }
            Airline al = Airline(Code, Name, Callsign, Country);
            airlines.push_back(al);
        }
    }
}

void readFlights(Graph &g, hTable &hT) { // O(E * n)
    ifstream infile("data/flights.csv");
    string line;
    bool first = true;
    while (getline(infile, line)) {
        if (first) { first = false;}
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }
            istringstream iss(line);
            string Source,Target,Airline;
            iss >> Source >> Target >> Airline;

            int src = hT[Source].getId();
            int tgt = hT[Target].getId();
            g.addFlight(src, tgt, Airline);
        }
    }
}

Airport getClosest(Airport ap, Graph g, hTable hT) { // O(E)
    int n = g.getClosestAirport(ap.getId(), hT);
    return hT[g.airportIDToCode(n)];
}

int main() {
    hTable hT1;
    vector<Airline> airlines;
    Graph g = readAirports(hT1);
    readAirlines(airlines);
    readFlights(g, hT1);
    for (auto ap : hT1) {
        g.setAirportCode((ap.second).getId(), (ap.second).getCode());
    }
    return 0;
}
