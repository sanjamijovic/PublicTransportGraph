#ifndef POOP_P1_LOCATION_H
#define POOP_P1_LOCATION_H


#include <iostream>

class Location {
public:
    Location(double latitude, double longitude);

    double getLatitude() const;
    double  getLongitude() const;

    static double distance(const Location&, const Location&);

    friend std::ostream& operator<< (std::ostream&, const Location&);

private:
    double latitude_, longitude_;
};


#endif //POOP_P1_LOCATION_H
