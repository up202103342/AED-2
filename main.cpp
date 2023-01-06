#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

void readAirports() {
    ifstream infile("data/airports.csv");
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
            string Code,Name,City,Country;
            int Latitude,Longitude;
            iss >> Code >> Name >> City >> Country >> Latitude >> Longitude;

            //...

        }
    }
}

void readAirlines() {
    ifstream infile("data/airlines.csv");
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
            string Code,Name,Callsign,Country;
            iss >> Code >> Name >> Callsign >> Country;

            //...

        }
    }
}

void readFlights(Graph graph) {
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

            //...

        }
    }
}

int main() {
    return 0;
}
