#ifndef AIRLINE_H
#define AIRLINE_H

#include <iostream>

using namespace std;

class Airline {
public:
    Airline();
    Airline(string code, string name, string callsign, string country);
    void setCode(string code);
    void setName(string name);
    void setCallsign(string callsign);
    void setCountry(string country);
    string getCode();
    string getName();
    string getCallsign();
    string getCountry();
private:
    string code;
    string name;
    string callsign;
    string country;
};

#endif