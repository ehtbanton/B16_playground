#include "Store.h"

Store::Store(int id, double x, double y)
    : Location(id, x, y) {}

Store::~Store() {
    for (Robot* robot : robotFleet) {
        delete robot;
    }
    robotFleet.clear();
}

void Store::addRobot(Robot* robot) {
    robotFleet.push_back(robot);
}

std::vector<Robot*>& Store::getRobotFleet() {
    return robotFleet;
}