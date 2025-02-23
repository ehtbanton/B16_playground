#ifndef MAP_H
#define MAP_H

#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include "Location.h"
#include "Store.h"
#include "Customer.h"

class Map {
private:
    std::vector<std::vector<double>> distances;  // Adjacency matrix
    std::vector<Location*> nodes;
    const double MAX_DISTANCE = 1.0;  // 1km maximum

public:
    Map();
    ~Map();

    // Main functions
    void initializeMap(Store* store, std::vector<Customer*>& customers);
    bool verifyConnectivity();

    // Utility functions
    double getDistance(int from, int to) const;
    int getNumNodes() const;
    Location* getNode(int index) const;
};

#endif // MAP_H