#ifndef POOP_P1_BUSSTOP_H
#define POOP_P1_BUSSTOP_H

#include <string>
#include <vector>
#include <iostream>
#include "location.h"

class BusLine;

class BusStop {
public:

    BusStop(int stopID, const std::string& stopName, Location location, int zoneID);

    int getStopID_() const;
    const std::string& getStopName_() const;
    int getZoneID_() const;
    const Location &getLocation_() const;

    friend std::ostream& operator<<(std::ostream&, const BusStop&);

private:
    int stopID_;
    std::string stopName_;
    Location location_;
    int zoneID_;
    std::vector<BusLine *> lines_;
};


#endif //POOP_P1_BUSSTOP_H
