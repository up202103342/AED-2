#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "Airport.h"
#include "Airline.h"
#include "Flight.h"

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
        if (ap1.getCode() == ap2.getCode()) return true;
        return false;
    }
};

typedef unordered_set<Airport, hFunc,eqFunc> hTable;

//---------------------------------

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
            float Latitude,Longitude;
            iss >> Code >> Name >> City >> Country >> Latitude >> Longitude;

            Airport ap = Airport(Code, Name, City, Country, Latitude, Longitude);
            hTable hT1;
            hT1.insert(ap);

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

            Airline al = Airline(Code, Name, Callsign, Country);
        }
    }
}

void readFlights() {
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

            Flight fl = Flight(Source, Target, Airline);

        }
    }
}


int main() {
    return 0;
}
