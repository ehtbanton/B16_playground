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

    // Private utility function
    void dfs(int node, std::vector<bool>& visited) const;
    int findNodeIndex(int id) const;  // Helper to find node index from ID

public:
    Map();
    ~Map();

    void initializeMap(Store* store, std::vector<Customer*>& customers);
    double getDistance(int fromId, int toId) const;
    std::vector<int> findShortestPath(int fromId, int toId) const;
    Location* getLocation(int id) const;
    int getNumNodes() const;
    bool verifyConnectivity() const;
};

#endif