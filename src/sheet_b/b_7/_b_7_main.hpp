
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


#include <iomanip>
#include "Tests.h"

void b7_test() {
	Tests::runAllTests();
}




void b7_run_delivery_system() {
    // Initialize store at the center (0,0) with just one robot
    Store* store = new Store(0, 0.0, 0.0);
    Robot* robot = new Robot();
    store->addRobot(robot);

    // Create delivery system
    DeliverySystem system(store);

    // Create 10 customers in random locations within 1km radius
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.7, 0.7); // Leave some margin from 1km limit

    std::vector<Customer*> customers;
    for (int i = 1; i <= 10; i++) {
        double x = dis(gen);
        double y = dis(gen);
        Customer* customer = new Customer(i, x, y);
        customers.push_back(customer);
        system.addCustomer(customer);
    }

    // Generate random orders (simulating a day's worth of orders)
    std::uniform_int_distribution<> customer_dist(1, 10);  // Customer IDs 1-10
    std::uniform_int_distribution<> basket_dist(1, 2);     // 1-2 baskets
    std::uniform_int_distribution<> num_orders(3, 8);      // Random number of orders per day

    int total_orders = num_orders(gen);
    std::cout << "\nGenerating " << total_orders << " random orders for today:\n";

    std::vector<Order*> daily_orders;
    for (int i = 0; i < total_orders; i++) {
        int customerId = customer_dist(gen);
        int baskets = basket_dist(gen);

        Order* order = new Order(customerId, baskets);
        daily_orders.push_back(order);

        std::cout << "Order " << i + 1 << ": Customer " << customerId
            << " ordered " << baskets << " basket(s)\n";

        if (!system.addOrder(order)) {
            std::cout << "Failed to add order - customer " << customerId
                << " has reached their order limit\n";
        }
    }

    // Plan the deliveries
    std::cout << "\nPlanning deliveries...\n";
    if (system.planDeliveries()) {
        std::cout << "Successfully created delivery plans!\n\n";

        auto plans = system.getDeliveryPlans();
        Map* map = system.getMap();

        for (size_t i = 0; i < plans.size(); i++) {
            const auto& plan = plans[i];
            std::cout << "Trip " << i + 1 << ":\n";

            // Show orders for this trip
            std::cout << "Orders assigned: ";
            for (const auto& order : plan.orders) {
                std::cout << "Customer " << order->getCustomerId()
                    << " (" << order->getBasketCount() << " baskets) ";
            }
            std::cout << "\n";

            // Show complete route with distances
            std::cout << "Route: ";
            double tripDistance = 0;
            for (size_t j = 0; j < plan.route.size() - 1; j++) {
                std::cout << plan.route[j];
                double segmentDist = map->getDistance(plan.route[j], plan.route[j + 1]);
                tripDistance += segmentDist;
                std::cout << " -(" << std::fixed << std::setprecision(2)
                    << segmentDist << "km)-> ";
            }
            std::cout << plan.route.back() << "\n";
            std::cout << "Total trip distance: " << tripDistance << "km\n\n";
        }
    }

    // After printing delivery plans, add a connectivity table
    Map* map = system.getMap();
    std::cout << "\nDistance Matrix:\n";

    // Print header row
    std::cout << std::setw(4) << "To:" << std::setw(2) << " ";
    for (int j = 0; j < map->getNumNodes(); j++) {
        std::cout << std::setw(6) << j;
    }
    std::cout << "\nFrom:\n";

    // Print each row with distances
    for (int i = 0; i < map->getNumNodes(); i++) {
        std::cout << std::setw(4) << i << "  ";
        for (int j = 0; j < map->getNumNodes(); j++) {
            double dist = map->getDistance(i, j);
            if (dist > 0) {
                std::cout << std::fixed << std::setprecision(2) << std::setw(6) << dist;
            }
            else {
                std::cout << std::setw(6) << "-";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\nNote: '-' indicates no direct connection\n";

    // Cleanup
    delete store;  // Will delete robot
    for (auto customer : customers) {
        delete customer;
    }
}


// If we were using multiple robots of varying basket capacities, I'd add a method to the DeliverySystem class 
// to assign orders to robots based on their capacities. I'd probably also change the shortest path algorithm 
// so that it optimises the maximum delivery distance of the robots, rather than the total distance for all 
// orders. This would be better reflective of the overall time required to complete all deliveries.