#include "DeliverySystem.h"

DeliverySystem::DeliverySystem(Store* store) : store(store) {
    map = new Map();
}

DeliverySystem::~DeliverySystem() {
    delete map;
    for (auto order : orders) {
        delete order;
    }
}

bool DeliverySystem::addCustomer(Customer* customer) {
    if (customers.size() >= 10) return false;
    customers.push_back(customer);
    map->initializeMap(store, customers);
    return true;
}

bool DeliverySystem::addOrder(Order* order) {
    for (auto customer : customers) {
        if (customer->getId() == order->getCustomerId()) {
            if (customer->canPlaceOrder()) {
                customer->incrementOrderCount();
                orders.push_back(order);
                return true;
            }
            break;
        }
    }
    return false;
}

bool DeliverySystem::planDeliveries() {
    deliveryPlans.clear();

    // Get pending orders and combine orders for same customer
    std::vector<std::pair<int, int>> customerTotals;  // <customerId, total baskets>
    for (int i = 1; i <= 10; i++) {
        int totalBaskets = 0;
        for (auto order : orders) {
            if (order && order->getStatus() == OrderStatus::PENDING &&
                order->getCustomerId() == i) {
                totalBaskets += order->getBasketCount();
            }
        }
        if (totalBaskets > 0) {
            customerTotals.push_back(std::make_pair(i, totalBaskets));
        }
    }

    // Create plan with robot
    DeliveryPlan plan;
    plan.robot = store->getRobotFleet()[0];
    deliveryPlans.push_back(plan);

    // Keep planning trips until all deliveries are made
    while (!customerTotals.empty()) {
        std::vector<std::pair<int, int>> tripCustomers;
        int currentBaskets = 0;
        int currentLoc = store->getId();
        std::vector<int> currentRoute;
        currentRoute.push_back(store->getId());

        // Keep adding closest reachable customers until basket limit
        while (currentBaskets < 3 && !customerTotals.empty()) {
            // Find closest reachable customer from current location
            double shortestDist = std::numeric_limits<double>::infinity();
            int bestCustomerIndex = -1;
            std::vector<int> bestPath;

            for (size_t i = 0; i < customerTotals.size(); i++) {
                int customerId = customerTotals[i].first;
                int baskets = customerTotals[i].second;

                // Skip if would exceed capacity
                if (currentBaskets + baskets > 3) continue;

                // Find shortest path to this customer
                std::vector<int> path = map->findShortestPath(currentLoc, customerId);
                if (path.empty()) continue;

                // Calculate path distance
                double pathDist = 0;
                for (size_t j = 0; j < path.size() - 1; j++) {
                    pathDist += map->getDistance(path[j], path[j + 1]);
                }

                if (pathDist < shortestDist) {
                    shortestDist = pathDist;
                    bestCustomerIndex = i;
                    bestPath = path;
                }
            }

            if (bestCustomerIndex == -1) break;  // No reachable customers within capacity

            // Add this customer to the trip
            int customerId = customerTotals[bestCustomerIndex].first;
            int baskets = customerTotals[bestCustomerIndex].second;
            tripCustomers.push_back(std::make_pair(customerId, baskets));
            currentBaskets += baskets;

            // Add path to route (excluding starting point)
            for (size_t i = 1; i < bestPath.size(); i++) {
                currentRoute.push_back(bestPath[i]);
            }
            currentLoc = customerId;

            // Remove this customer from remaining deliveries
            customerTotals.erase(customerTotals.begin() + bestCustomerIndex);
        }

        // Add path back to store
        std::vector<int> returnPath = map->findShortestPath(currentLoc, store->getId());
        if (!returnPath.empty()) {
            for (size_t i = 1; i < returnPath.size(); i++) {
                currentRoute.push_back(returnPath[i]);
            }
        }

        // Add orders for this trip to the plan
        for (size_t i = 0; i < tripCustomers.size(); i++) {
            int customerId = tripCustomers[i].first;
            int basketsNeeded = tripCustomers[i].second;

            for (auto order : orders) {
                if (order && order->getStatus() == OrderStatus::PENDING &&
                    order->getCustomerId() == customerId && basketsNeeded > 0) {
                    deliveryPlans.back().orders.push_back(order);
                    order->updateStatus(OrderStatus::IN_PROGRESS);
                    basketsNeeded -= order->getBasketCount();
                }
            }
        }

        // Add route to plan
        deliveryPlans.back().route = currentRoute;

        // If there are more deliveries to make, start a new plan
        if (!customerTotals.empty()) {
            DeliveryPlan newPlan;
            newPlan.robot = store->getRobotFleet()[0];
            deliveryPlans.push_back(newPlan);
        }
    }

    return true;
}

bool DeliverySystem::canAddOrderToPlan(const DeliveryPlan& plan, Order* order) const {
    int currentLoad = 0;
    for (auto o : plan.orders) {
        currentLoad += o->getBasketCount();
    }
    return (currentLoad + order->getBasketCount()) <= 3;
}

void DeliverySystem::optimizeDeliveryPlans() {
    for (auto& plan : deliveryPlans) {
        if (plan.orders.empty()) continue;

        std::vector<int> route;
        route.push_back(store->getId());

        std::vector<bool> visited(plan.orders.size(), false);
        int currentLocation = store->getId();

        while (route.size() < plan.orders.size() + 1) {
            double minDist = std::numeric_limits<double>::infinity();
            int nextLocation = -1;
            int orderIndex = -1;

            for (size_t i = 0; i < plan.orders.size(); i++) {
                if (!visited[i]) {
                    int customerId = plan.orders[i]->getCustomerId();
                    std::vector<int> path = map->findShortestPath(currentLocation, customerId);

                    if (path.size() < 2) continue;

                    double dist = 0;
                    for (size_t j = 0; j + 1 < path.size(); j++) {
                        double segDist = map->getDistance(path[j], path[j + 1]);
                        if (segDist < 0) continue;
                        dist += segDist;
                    }

                    if (dist < minDist) {
                        minDist = dist;
                        nextLocation = customerId;
                        orderIndex = i;
                    }
                }
            }

            if (nextLocation == -1) break;

            route.push_back(nextLocation);
            visited[orderIndex] = true;
            currentLocation = nextLocation;
        }

        route.push_back(store->getId());
        plan.route = route;
    }
}

std::vector<DeliveryPlan> DeliverySystem::getDeliveryPlans() const {
    return deliveryPlans;
}

std::vector<Order*> DeliverySystem::getPendingOrders() const {
    std::vector<Order*> pending;
    for (auto order : orders) {
        if (order->getStatus() == OrderStatus::PENDING) {
            pending.push_back(order);
        }
    }
    return pending;
}

Map* DeliverySystem::getMap() const {
    return map;
}