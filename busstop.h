#ifndef POOP_P1_BUSSTOP_H
#define POOP_P1_BUSSTOP_H

#include <string>
#include <set>
#include <iostream>
#include "location.h"
#include "busline.h"

class BusStop {
public:

    BusStop(int stopID, const std::string& stopName, Location location, int zoneID);

    int getStopID_() const;
    const std::string& getStopName_() const;
    int getZoneID_() const;
    const Location &getLocation_() const;

    std::set<BusLine*> getLines();
    bool isStopForLine(BusLine*);

    friend void BusLine::addStop(BusStop* stop, Directions direction);
    friend void BusLine::removeStop(BusStop* stop, Directions direction);

    friend std::ostream& operator<<(std::ostream&, const BusStop&);

private:
    int stopID_;
    std::string stopName_;
    Location location_;
    int zoneID_;
    std::set<BusLine *> lines_;

    void addLine(BusLine *line);
    void removeLine(BusLine *line);
};


#endif //POOP_P1_BUSSTOP_H
