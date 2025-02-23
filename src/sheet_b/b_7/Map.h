#ifndef MAP_H
#define MAP_H

#include <vector>
#include <random>
#include "Location.h"
#include "Store.h"
#include "Customer.h"

class Map {
private:
    std::vector<std::vector<double>> distances;  // Adjacency matrix
    std::vector<Location*> nodes;
    const double MAX_DISTANCE = 1.0;  // 1km maximum

    // Private utility functions
    bool isConnected() const;  // Checks if graph is connected
    void dfs(int node, std::vector<bool>& visited) const;

public:
    Map();
    ~Map();

    void initializeMap(Store* store, std::vector<Customer*>& customers);
    double getDistance(int fromId, int toId) const;
    std::vector<int> findShortestPath(int fromId, int toId) const;
    Location* getLocation(int id) const;
    int getNumNodes() const;

    // For testing/verification
    bool verifyConnectivity() const;
    bool verifyDistances() const;  // Ensures no distance > 1km
};

#endif