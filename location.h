#ifndef PUBLICTRANSPORTGRAPH_LOCATION_H
#define PUBLICTRANSPORTGRAPH_LOCATION_H


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


#endif //PUBLICTRANSPORTGRAPH_LOCATION_H
