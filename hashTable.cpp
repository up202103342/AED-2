#include "Airport.h"
#include <unordered_map>
#include <string>

using namespace std;

struct hFunc {
    int operator() (const string& ap) const {
        unsigned long hash = 0;
        for(int i = 0; i < ap.length(); i++) {
            hash = (hash * 37) + int(ap[i]);
        }
        return hash % 3023;
    }
};

struct eqFunc {
    bool operator() (const string& apCode1, const string& apCode2) const {
        return apCode1==apCode2 ;
    }
};

typedef unordered_map<string, Airport, hFunc, eqFunc> hTable;
