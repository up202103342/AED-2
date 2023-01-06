#include "Airline.h"

Airline::Airline() {}

Airline::Airline(string code, string name, string callsign, string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

void Airline::setCode(string code) {
    this->code = code;
}

void Airline::setName(string name) {
    this->name = name;
}

void Airline::setCallsign(string callsign) {
    this->callsign = callsign;
}

void Airline::setCountry(string country) {
    this->country = country;
}
string Airline::getCode() {
    return code;
}

string Airline::getName() {
    return name;
}

string Airline::getCallsign() {
    return callsign;
}

string Airline::getCountry() {
    return country;
}