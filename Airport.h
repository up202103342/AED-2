
#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>

using namespace std;

class Airport {
public:
    Airport();
    Airport(int id, string code, string name, string city, string country, float latitude, float longitude);
    void setCode(string code);
    void setName(string name);
    void setCity(string city);
    void setCountry(string country);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    int getId() const;
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;

    int getID();

private:
    int id;
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

};

#endif