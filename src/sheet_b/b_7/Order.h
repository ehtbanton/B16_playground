#ifndef ORDER_H
#define ORDER_H

enum class OrderStatus { // enum class is used to avoid name clashes
    PENDING,
    IN_PROGRESS,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    int customerId;
    int basketCount;
    OrderStatus status;

public:
    Order(int customerId, int basketCount);

    void updateStatus(OrderStatus newStatus);
    int getCustomerId() const;
    int getBasketCount() const;
    OrderStatus getStatus() const;
};

#endif