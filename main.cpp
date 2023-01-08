#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"
#include "Display.h"

using namespace std;

//Esta funcao le o ficheiro airports.csv e introduz os dados na hash table, criando ed evolvendo depois o grafo. Complexidade temporal: O(V * n)
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

//Esta funcao le o ficheiro airlines.csv e introduz os dados no vetor airlines. Complexidade temporal: O(n^2)
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
//Esta funcao le o ficheiro flights.csv e introduz os dados no grafo. Complexidade temporal: O(E * n)
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

//Esta funcao devolve o aeroporto mais proximo a um dado aeroporto. Complexidade temporal: O(E)
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
    Display dp;
    dp.displayMenu();
    string input;
    cout << '\n';
    while (!(dp.getState() == "menu" && input == "Quit")) {
        cout << "Enter input:\n";
        getline(std::cin, input);
        cout << ".............\n";
        dp.processInput(input);
        if (dp.getState()=="menu") dp.displayMenu();
        else if (dp.getState()=="locais") dp.displayLocais();
        else if (dp.getState()=="localPartida") dp.displayLocalPartida();
        else if (dp.getState()=="localChegada") {
            dp.displayLocalChegada();
            cout << "Enter input:\n";
            getline(std::cin, input);
            cout << ".............\n";
            dp.processInput(input);
            dp.displayVoo(hT1, g);
        }
        else if (dp.getState()=="info") dp.displayInfo();
        else if (dp.getState()=="insertAirport") dp.displayChooseInfo(), dp.displayAirportInfo(g, hT1);
        else if (dp.getState()=="insertAirline") dp.displayChooseInfo(), dp.displayAirlineInfo(g, hT1);
        else if (dp.getState()=="insertCountry") dp.displayChooseInfo(), dp.displayCountryInfo(g, hT1);
    }
    return 0;
}
