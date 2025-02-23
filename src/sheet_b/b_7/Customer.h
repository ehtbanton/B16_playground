#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Location.h"

class Customer : public Location {
private:
    static const int MAX_ORDERS = 2;
    int orderCount;

public:
    Customer(int id, double x, double y);
    bool canPlaceOrder() const;
    void incrementOrderCount();
    void decrementOrderCount();
    int getOrderCount() const;
};

#endif // CUSTOMER_H