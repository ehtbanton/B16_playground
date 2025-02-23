#ifndef LOCATION_H
#define LOCATION_H

class Location {
private:
    int id;
    double x;
    double y;

public:
    Location(int id, double x, double y);
    virtual ~Location() = default;

    int getId() const;
    double getX() const;
    double getY() const;
    void setCoordinates(double x, double y);
};

#endif // LOCATION_H