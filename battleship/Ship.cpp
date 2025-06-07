#include "Ship.h"

Ship::Ship() {}

void Ship::addCoordinate(string coord) {
    coordinates.push_back(coord);
}
/*Returns a read-only reference to the coordinates vector.
    The first 'const' means the vector can't be modified.
    The second 'const' means this method doesn't change the Ship object.*/
const vector<string>& Ship::getCoordinates() const {
    return coordinates;
}

