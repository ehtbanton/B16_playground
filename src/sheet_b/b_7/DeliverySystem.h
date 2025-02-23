#ifndef DELIVERY_SYSTEM_H
#define DELIVERY_SYSTEM_H

#include <vector>
#include <map>
#include "Store.h"
#include "Customer.h"
#include "Order.h"
#include "Map.h"

class DeliverySystem {
private:
    Store* store;
    std::vector<Customer*> customers;
    std::vector<Order*> orders;
    Map* map;
    std::map<int, std::vector<int>> routes;  // Robot ID to route mapping

public:
    DeliverySystem(Store* store);
    ~DeliverySystem();

    void addCustomer(Customer* customer);
    bool addOrder(Order* order);
    bool planDelivery();
    void displayRoutes() const;
};

#endif // DELIVERY_SYSTEM_H