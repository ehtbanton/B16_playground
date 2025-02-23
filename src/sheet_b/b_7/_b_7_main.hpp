
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
├── DeliverySystem.h/cpp (Main Controller)
│    ├── Has: Store
│    ├── Has: Customers
│    ├── Has: Map
│    ├── Has: Robots
│    └── Has: Orders
│
├── Constants.h
│	├── MAX_DISTANCE (1.0)
│	├── MAX_CUSTOMERS (10)
│	├── MAX_BASKETS_PER_CUSTOMER (2)
│	└── ROBOT_BASKET_CAPACITY (3)
│
└── Utilities.h

*/