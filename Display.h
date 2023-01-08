#ifndef AED2_DISPLAY_H
#define AED2_DISPLAY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>

#include "Graph.h"

using namespace std;

class Display {
    string state;
    int numPicked;
    string letterPicked;
    float coordLat1;
    float coordLon1;
    float coordLat2;
    float coordLon2;
    string apCode1;
    string apCode2;
    string city1;
    string city2;

public:
    Display();

    void displayMenu();

    void processInput(string input);

    void displayLocais();

    void displayLocalPartida();

    void displayLocalChegada();

    void displayVoo(hTable, Graph);

    void displayInfo();

    void displayAbout();

    //Getters n' Setters
    string getState() const;
    void setState(string state);
    const int &getNumPicked() const;
    void setNumPicked(const int &numPicked);
    const string &getLetterPicked() const;
    void setLetterPicked(const string &letterPicked);
    float getCoordLat1() const;
    float getCoordLon1() const;
    float getCoordLat2() const;
    float getCoordLon2() const;
    const string &getApCode1() const;
    const string &getApCode2() const;
    const string &getCity1() const;
    const string &getCity2() const;
    void setApCode1(const string &apCode1);
    void setApCode2(const string &apCode2);
    void setCoordLat1(const float &coordLat1) ;
    void setCoordLon1(const float &coordLon1) ;
    void setCoordLat2(const float &coordLat2) ;
    void setCoordLon2(const float &coordLon2) ;
    void setCity1(const string &city1);
    void setCity2(const string &city2);

    void reset();
};


#endif //AED2_DISPLAY_H
