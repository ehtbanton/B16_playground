
/*

- We have a grocery store delivery system
- 10 customers are subscribed
- Robot can carry 3 baskets at once
- Each customer can order max 2 baskets
- All locations must be within 1km of each other
- All locations connect to store (directly or indirectly)


Class set map:
│
├── Location.h/cpp
│   ├── id
│   ├── coordinates (x,y)
│   └── getters/setters
│
├── Store.h/cpp (inherits Location)
│   └── robotFleet
│
├── Customer.h/cpp (inherits Location)
│   ├── maxOrders (2)
│   └── orderCount
│
├── Map.h/cpp
│   ├── nodes vector
│   ├── distance matrix
│   └── pathfinding methods
│
├── Robot.h/cpp
│   ├── basketCapacity (3)
│   └── delivery methods
│
├── Order.h/cpp
│   ├── customerId
│   ├── basketCount
│   └── status
│
└── DeliverySystem.h/cpp (Main Controller)
    ├── Has: Store
    ├── Has: Customers
    ├── Has: Map
    ├── Has: Robots
    └── Has: Orders


*/


#include <iostream>
#include <cassert>
#include "Location.h"

void testLocation() {
    // Test constructor and getters
    Location loc(1, 0.5, 0.5);
    assert(loc.getId() == 1);
    assert(loc.getX() == 0.5);
    assert(loc.getY() == 0.5);

    // Test setCoordinates
    loc.setCoordinates(0.7, 0.3);
    assert(loc.getX() == 0.7);
    assert(loc.getY() == 0.3);

    std::cout << "Location tests passed!\n";
}

int b7_test_main() {
    testLocation();
    std::cout << "All tests passed!\n";
    return 0;
}
