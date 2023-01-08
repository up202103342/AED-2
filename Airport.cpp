#include "Airport.h"

Airport::Airport() {}

Airport::Airport(int id, string code, string name, string city, string country, float latitude, float longitude) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

void Airport::setCode(string code) {
    this->code = code;
}

void Airport::setName(string name) {
    this->name = name;
}

void Airport::setCity(string city) {
    this->city = city;
}

void Airport::setCountry(string country) {
    this->country = country;
}

void Airport::setLatitude(float latitude) {
    this->latitude = latitude;
}

void Airport::setLongitude(float longitude) {
    this->longitude = longitude;
}

int Airport::getId() const{
    return id;
}

string Airport::getCode() const{
    return code;
}

string Airport::getName() const{
    return name;
}

string Airport::getCity() const{
    return city;
}

string Airport::getCountry() const{
    return country;
}

float Airport::getLatitude() const{
    return latitude;
}

float Airport::getLongitude() const{
    return longitude;
}

