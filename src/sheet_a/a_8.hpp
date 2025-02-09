

/*
Question 8



a) Class hierarchy:

    GeometricObject
    |
    |--Point
    |--Line
    |--Plane
    |--QuadricSurface
       |--Cube
       |--Ellipsoid
       |--Quadric
       |--Cone
       |--Cuboid

b) See below.

c) Because certain methods will be functionally identical across all different 3D objects, making the objects 
   be derived from a common base class reduces code repetition, which increases the code's maintainabiliry

*/


class GeometricObject { // base class
protected:
    // Position in 3D space
    double x, y, z;
    // Orientation (simplified to single angle for brevity)
    double orientation;

public:
    GeometricObject(double x = 0, double y = 0, double z = 0, double orientation = 0){
		this->x = x;
		this->y = y;
		this->z = z;
		this->orientation = orientation;
    }

	// Virtual functions will look for implementation in the derived classes
    virtual void draw() = 0;
    virtual ~GeometricObject() {}
};


