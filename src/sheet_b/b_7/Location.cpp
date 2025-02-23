#include "Location.h"

Location::Location(int id, double x, double y)
    : id(id), x(x), y(y) {}

int Location::getId() const { return id; }
double Location::getX() const { return x; }
double Location::getY() const { return y; }

void Location::setCoordinates(double newX, double newY) {
    x = newX;
    y = newY;
}