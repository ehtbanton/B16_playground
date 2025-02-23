#include "Order.h"

Order::Order(int customerId, int basketCount)
    : customerId(customerId),
    basketCount(basketCount),
    status(OrderStatus::PENDING) {}

void Order::updateStatus(OrderStatus newStatus) {
    status = newStatus;
}

int Order::getCustomerId() const {
    return customerId;
}

int Order::getBasketCount() const {
    return basketCount;
}

OrderStatus Order::getStatus() const {
    return status;
}