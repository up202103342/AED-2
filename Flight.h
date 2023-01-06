#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>

using namespace std;

class Flight {
public:
    Flight();
    Flight(string source, string target, string airline);
    void setSource(string source);
    void setTarget(string target);
    void setAirline(string airline);
    string getSource();
    string getTarget();
    string getAirline();
private:
    string source;
    string target;
    string airline;
};

#endif