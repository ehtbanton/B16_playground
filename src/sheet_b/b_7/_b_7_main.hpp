
/*

Class set map:

Location
├── Store (inherits from Location)
└── CustomerHouse (inherits from Location)

DeliveryNode
├── Position (x,y coordinates)
└── Connections (list of connected nodes)

Route
├── List<DeliveryNode>
└── TotalDistance

Robot
├── CurrentPosition
├── BasketCapacity (3)
└── CurrentLoad

Order
├── CustomerID
├── NumberOfBaskets (max 2)
└── Status

DeliverySystem
├── TopologicalMap
│   ├── Nodes (Store + Houses)
│   └── Connections
├── OrderQueue
├── Robots
└── RouteOptimizer









*/