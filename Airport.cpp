#include "Airport.h"

Airport::Airport() {}

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) {
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

string Airport::getCode() {
    return code;
}

string Airport::getName() {
    return name;
}

string Airport::getCity() {
    return city;
}

string Airport::getCountry() {
    return country;
}

float Airport::getLatitude() {
    return latitude;
}

float Airport::getLongitude() {
    return longitude;
}