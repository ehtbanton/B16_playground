#pragma once
#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <cassert>
#include "Location.h"
#include "Store.h"
#include "Customer.h"
#include "Robot.h"
#include "Order.h"

class Tests {
public:
    static void testLocation() {
        Location loc(1, 0.5, 0.5);
        assert(loc.getId() == 1);
        assert(loc.getX() == 0.5);
        assert(loc.getY() == 0.5);

        loc.setCoordinates(0.7, 0.3);
        assert(loc.getX() == 0.7);
        assert(loc.getY() == 0.3);

        std::cout << "Location tests passed!\n";
    }

    static void testCustomer() {
        Customer cust(2, 0.3, 0.4);

        // Test inheritance
        assert(cust.getId() == 2);
        assert(cust.getX() == 0.3);
        assert(cust.getY() == 0.4);

        // Test order management
        assert(cust.getOrderCount() == 0);
        assert(cust.canPlaceOrder() == true);

        cust.incrementOrderCount();
        assert(cust.getOrderCount() == 1);
        assert(cust.canPlaceOrder() == true);

        cust.incrementOrderCount();
        assert(cust.getOrderCount() == 2);
        assert(cust.canPlaceOrder() == false);

        cust.decrementOrderCount();
        assert(cust.getOrderCount() == 1);
        assert(cust.canPlaceOrder() == true);

        std::cout << "Customer tests passed!\n";
    }

    static void testStore() {
        Store store(3, 0.0, 0.0);

        // Test inheritance
        assert(store.getId() == 3);
        assert(store.getX() == 0.0);
        assert(store.getY() == 0.0);

        // Test robot fleet management
        assert(store.getRobotFleet().empty());

        Robot* robot = new Robot();
        store.addRobot(robot);
        assert(store.getRobotFleet().size() == 1);

        std::cout << "Store tests passed!\n";
    }

    static void testRobot() {
        Robot robot;

        // Test initial state
        assert(robot.getCurrentLoad() == 0);
        assert(robot.getCurrentLocation() == nullptr);

        // Test basket loading
        assert(robot.loadBaskets(2) == true);  // Should succeed
        assert(robot.getCurrentLoad() == 2);

        assert(robot.loadBaskets(2) == false); // Should fail (over capacity)
        assert(robot.getCurrentLoad() == 2);   // Load shouldn't change

        // Test delivery
        Location* dest = new Location(5, 0.5, 0.5);
        assert(robot.deliver(dest) == true);
        assert(robot.getCurrentLocation() == dest);

        delete dest;
        std::cout << "Robot tests passed!\n";
    }

    static void testOrder() {
        Order order(1, 2);  // Customer ID 1, 2 baskets

        // Test initial state
        assert(order.getCustomerId() == 1);
        assert(order.getBasketCount() == 2);
        assert(order.getStatus() == OrderStatus::PENDING);

        // Test status updates
        order.updateStatus(OrderStatus::IN_PROGRESS);
        assert(order.getStatus() == OrderStatus::IN_PROGRESS);

        order.updateStatus(OrderStatus::DELIVERED);
        assert(order.getStatus() == OrderStatus::DELIVERED);

        std::cout << "Order tests passed!\n";
    }

    static void runAllTests() {
        testLocation();
        testCustomer();
        testStore();
        testRobot();
        testOrder();
        std::cout << "\nAll tests passed!\n";
    }
};

#endif