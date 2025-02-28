#ifndef STORE_H
#define STORE_H

#include <vector>
#include "Location.h"
#include "Robot.h"

class Store : public Location {
private:
    std::vector<Robot*> robotFleet;

public:
    Store(int id, double x, double y);
    ~Store();

    void addRobot(Robot* robot);
    std::vector<Robot*>& getRobotFleet();
};

#endif