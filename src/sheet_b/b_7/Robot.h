#ifndef ROBOT_H
#define ROBOT_H

#include "Location.h"

class Robot {
private:
    static const int BASKET_CAPACITY = 3;
    int currentLoad;
    Location* currentLocation;

public:
    Robot();

    bool loadBaskets(int count);
    bool deliver(Location* destination);
    int getCurrentLoad() const;
    Location* getCurrentLocation() const;
    void setCurrentLocation(Location* location);
};

#endif