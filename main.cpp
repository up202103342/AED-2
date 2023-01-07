#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_set>

#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
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

void readAirports() {
    int n;
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
            n++;
            Airport ap = Airport(n, Code, Name, City, Country, Latitude, Longitude);
            hTable hT1;
            hT1.insert(ap);
        }
    }
    Graph g(n);
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

void readFlights(Graph g) {
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


void getClosest(Graph g, Airport a1){
    int d=INT64_MAX;
    for(auto a2 : g.getConnectedAirports(a1.getId())){
        if(d< haversine(a1.getLatitude(), a1.getLongitude()), )
    }
    return ;
}



int main() {
    return 0;
}
