#include "Flight.h"

Flight::Flight() {}

Flight::Flight(string source, string target, string airline) {
    this->source = source;
    this->target = target;
    this->airline = airline;
}

void Flight::setSource(string source) {
    this->source = source;
}

void Flight::setTarget(string target) {
    this->target = target;
}

void Flight::setAirline(string airline) {
    this->airline = airline;
}

string Flight::getSource() {
    return source;
}

string Flight::getTarget() {
    return target;
}

string Flight::getAirline() {
    return airline;
}