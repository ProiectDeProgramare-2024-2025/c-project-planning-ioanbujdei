#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
using namespace std;

class Ship {
private:
    vector<string> coordinates;
public:
    Ship();
    void addCoordinate(string coord); // Add a coordinate to the ship
    const vector<string>& getCoordinates() const; // Access ship coordinates
};

#endif

