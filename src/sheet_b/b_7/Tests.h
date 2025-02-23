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
#include "Map.h"

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

    static void testMap() {
        // Create a store and some customers
        Store* store = new Store(0, 0.0, 0.0);
        std::vector<Customer*> customers;
        for (int i = 1; i <= 5; i++) {
            customers.push_back(new Customer(i, 0.1 * i, 0.1 * i));
        }

        Map map;
        map.initializeMap(store, customers);

        // Test basic properties
        assert(map.getNumNodes() == 6);  // Store + 5 customers
        assert(map.verifyConnectivity());  // Graph should be connected

        // Test pathfinding
        std::vector<int> path = map.findShortestPath(0, 5);  // From store to last customer
        assert(!path.empty());  // Should find a path
        assert(path[0] == 0);   // Should start at store
        assert(path.back() == 5);  // Should end at customer 5

        // Clean up
        delete store;
        for (auto customer : customers) {
            delete customer;
        }

        std::cout << "Map tests passed!\n";
    }


    static void runAllTests() {
        testLocation();
        testCustomer();
        testStore();
        testRobot();
        testOrder();
		testMap();
        std::cout << "\nAll tests passed!\n";
    }
};

#endif