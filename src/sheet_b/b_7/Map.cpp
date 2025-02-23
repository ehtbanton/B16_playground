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
    distances.clear(); // Clear existing distances

    // Add store and customers to nodes
    if (store) {
        nodes.push_back(store);
    }

    for (auto customer : customers) {
        if (customer) {
            nodes.push_back(customer);
        }
    }

    int n = nodes.size();
    // Properly resize the distances matrix
    distances.resize(n);
    for (auto& row : distances) {
        row.resize(n, -1);  // Initialize all distances to -1
    }

    // Initialize random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, MAX_DISTANCE);

    // Connect store to all customers first to ensure base connectivity
    for (int i = 1; i < n; i++) {
        double distance = dis(gen);
        distances[0][i] = distance;
        distances[i][0] = distance;
    }

    // Add some additional random connections between customers
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 0) {  // 50% chance of connection
                double distance = dis(gen);
                distances[i][j] = distance;
                distances[j][i] = distance;
            }
        }
    }
}

std::vector<int> Map::findShortestPath(int fromId, int toId) const {
    if (nodes.empty()) return std::vector<int>();

    int fromIdx = findNodeIndex(fromId);
    int toIdx = findNodeIndex(toId);

    if (fromIdx < 0 || toIdx < 0) return std::vector<int>();

    int n = nodes.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    dist[fromIdx] = 0;

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
            if (v < distances[u].size() && distances[u][v] > 0) {
                double alt = dist[u] + distances[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }

    std::vector<int> path;
    int current = toIdx;

    // Prevent infinite loop if path doesn't exist
    while (current != -1 && path.size() <= nodes.size()) {
        if (current >= 0 && current < nodes.size() && nodes[current]) {
            path.push_back(nodes[current]->getId());
        }
        current = prev[current];
    }

    if (path.empty() || path.back() != fromId) {
        return std::vector<int>();  // No valid path found
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

int Map::findNodeIndex(int id) const {
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] && nodes[i]->getId() == id) return i;
    }
    return -1;
}