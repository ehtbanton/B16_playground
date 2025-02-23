#include "Map.h"
#include <queue>
#include <limits>
#include <algorithm>

Map::Map() {}

Map::~Map() {
    // Note: We don't delete the Location pointers as they're managed elsewhere
    nodes.clear();
    distances.clear();
}

void Map::initializeMap(Store* store, std::vector<Customer*>& customers) {
    nodes.clear();

    // Add store and customers to nodes
    nodes.push_back(store);
    for (auto customer : customers) {
        nodes.push_back(customer);
    }

    int n = nodes.size();
    distances.resize(n, std::vector<double>(n, -1));  // -1 indicates no direct connection

    // Initialize random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, MAX_DISTANCE);

    // Connect store to about half of the customers randomly
    int directConnections = n / 2;
    std::vector<bool> isConnected(n, false);
    isConnected[0] = true;  // Store is always connected

    // First, connect store to some random customers
    for (int i = 0; i < directConnections; i++) {
        int customerIdx = (rand() % (n - 1)) + 1;
        if (!isConnected[customerIdx]) {
            double distance = dis(gen);
            distances[0][customerIdx] = distance;
            distances[customerIdx][0] = distance;
            isConnected[customerIdx] = true;
        }
    }

    // Connect remaining customers through other customers
    for (int i = 1; i < n; i++) {
        if (!isConnected[i]) {
            int connectedNode = -1;
            do {
                connectedNode = rand() % n;
            } while (!isConnected[connectedNode] || connectedNode == i);

            double distance = dis(gen);
            distances[i][connectedNode] = distance;
            distances[connectedNode][i] = distance;
            isConnected[i] = true;
        }
    }

    // Add some additional random connections
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 3 == 0) {  // 33% chance of additional connection
                double distance = dis(gen);
                distances[i][j] = distance;
                distances[j][i] = distance;
            }
        }
    }
}

std::vector<int> Map::findShortestPath(int fromId, int toId) const {
    int n = nodes.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    // Find node indices from IDs
    int fromIdx = -1, toIdx = -1;
    for (int i = 0; i < n; i++) {
        if (nodes[i]->getId() == fromId) fromIdx = i;
        if (nodes[i]->getId() == toId) toIdx = i;
    }

    if (fromIdx == -1 || toIdx == -1) return std::vector<int>();

    dist[fromIdx] = 0;

    // Dijkstra's algorithm
    for (int i = 0; i < n; i++) {
        int u = -1;
        double minDist = std::numeric_limits<double>::infinity();

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (distances[u][v] > 0) {  // If there's a connection
                double alt = dist[u] + distances[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }

    // Reconstruct path
    std::vector<int> path;
    int current = toIdx;
    while (current != -1) {
        path.push_back(nodes[current]->getId());
        current = prev[current];
    }
    std::reverse(path.begin(), path.end());

    return path;
}

bool Map::verifyConnectivity() const {
    std::vector<bool> visited(nodes.size(), false);
    dfs(0, visited);  // Start DFS from store (index 0)
    return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

void Map::dfs(int node, std::vector<bool>& visited) const {
    visited[node] = true;
    for (int i = 0; i < nodes.size(); i++) {
        if (distances[node][i] > 0 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

double Map::getDistance(int fromId, int toId) const {
    int fromIdx = -1, toIdx = -1;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->getId() == fromId) fromIdx = i;
        if (nodes[i]->getId() == toId) toIdx = i;
    }
    if (fromIdx != -1 && toIdx != -1) {
        return distances[fromIdx][toIdx];
    }
    return -1;
}

Location* Map::getLocation(int id) const {
    for (auto node : nodes) {
        if (node->getId() == id) return node;
    }
    return nullptr;
}

int Map::getNumNodes() const {
    return nodes.size();
}