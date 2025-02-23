#include "Customer.h"

Customer::Customer(int id, double x, double y)
    : Location(id, x, y), orderCount(0) {}

bool Customer::canPlaceOrder() const {
    return orderCount < MAX_ORDERS;
}

void Customer::incrementOrderCount() {
    if (orderCount < MAX_ORDERS) {
        orderCount++;
    }
}

void Customer::decrementOrderCount() {
    if (orderCount > 0) {
        orderCount--;
    }
}

int Customer::getOrderCount() const {
    return orderCount;
}