#ifndef DELIVERY_SYSTEM_H
#define DELIVERY_SYSTEM_H

#include <vector>
#include "Store.h"
#include "Customer.h"
#include "Order.h"
#include "Map.h"
#include "Robot.h"

// Simple struct to hold delivery plan details
struct DeliveryPlan {
    Robot* robot;
    std::vector<Order*> orders;
    std::vector<int> route;
};

class DeliverySystem {
private:
    Store* store;
    std::vector<Customer*> customers;
    std::vector<Order*> orders;
    Map* map;
    std::vector<DeliveryPlan> deliveryPlans;

    // Helper functions
    bool canAddOrderToPlan(const DeliveryPlan& plan, Order* order) const;
    void optimizeDeliveryPlans();

public:
    DeliverySystem(Store* store);
    ~DeliverySystem();

    bool addCustomer(Customer* customer);
    bool addOrder(Order* order);
    bool planDeliveries();

    // Getters for testing
    std::vector<DeliveryPlan> getDeliveryPlans() const;
    std::vector<Order*> getPendingOrders() const;
    Map* getMap() const;
};

#endif