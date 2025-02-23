#include "Robot.h"

Robot::Robot() : currentLoad(0), currentLocation(nullptr) {}

bool Robot::loadBaskets(int count) {
    if (currentLoad + count <= BASKET_CAPACITY) {
        currentLoad += count;
        return true;
    }
    return false;
}

bool Robot::deliver(Location* destination) {
    if (destination && currentLoad > 0) {
        currentLocation = destination;
        return true;
    }
    return false;
}

int Robot::getCurrentLoad() const {
    return currentLoad;
}

Location* Robot::getCurrentLocation() const {
    return currentLocation;
}

void Robot::setCurrentLocation(Location* location) {
    currentLocation = location;
}