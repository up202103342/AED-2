
#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>

using namespace std;

class Airport {
public:
    Airport();
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    void setCode(string code);
    void setName(string name);
    void setCity(string city);
    void setCountry(string country);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    float getLatitude();
    float getLongitude();
private:
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

};

#endif