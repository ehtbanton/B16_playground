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

    // Get pending orders
    std::vector<Order*> pendingOrders;
    for (auto order : orders) {
        if (order && order->getStatus() == OrderStatus::PENDING) {
            pendingOrders.push_back(order);
        }
    }

    if (pendingOrders.empty()) {
        return true;  // No orders to process
    }

    // Get available robots
    std::vector<Robot*> availableRobots = store->getRobotFleet();
    if (availableRobots.empty()) {
        return false;
    }

    // Initialize plans
    for (auto robot : availableRobots) {
        if (robot) {
            DeliveryPlan plan;
            plan.robot = robot;
            plan.route.push_back(store->getId());  // Start at store
            deliveryPlans.push_back(plan);
        }
    }

    // Simple assignment: assign orders sequentially to plans
    size_t currentPlan = 0;
    for (auto order : pendingOrders) {
        if (!order) continue;

        bool assigned = false;
        for (size_t i = 0; i < deliveryPlans.size(); i++) {
            if (canAddOrderToPlan(deliveryPlans[i], order)) {
                deliveryPlans[i].orders.push_back(order);
                deliveryPlans[i].route.push_back(order->getCustomerId());
                assigned = true;
                break;
            }
        }

        if (!assigned) {
            return false;  // Couldn't assign order
        }
    }

    // Finalize routes
    for (auto& plan : deliveryPlans) {
        if (!plan.route.empty()) {
            plan.route.push_back(store->getId());  // Return to store
        }
    }

    // Update order statuses
    for (auto& plan : deliveryPlans) {
        for (auto order : plan.orders) {
            if (order) {
                order->updateStatus(OrderStatus::IN_PROGRESS);
            }
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